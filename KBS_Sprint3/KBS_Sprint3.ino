#include <Wire.h>
#include "Player_IR.h"
#include <SPI.h>
#include <stdint.h>
#include <MI0283QT9.h>
#include "GameField.h"
#include "NunchukLibrary.h"
#include "Player_NC.h"
#include "Menu.h"
#include "OptionMenu.h"
#include "Touch.h"
#include "irRecv.h"
#include "irSend.h"
#include "Timer_Display.h"
#include "AfterGame.h"
#include "SaveHighScore.h"
#include "WatchHighScore.h"


#define ADDRESS 0x52
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13

uint8_t gameStatus = 1;
uint8_t levelSelect = 1;
uint8_t OnehzCounter = 0;
uint8_t gameTimer = 0;
int highscore;

uint8_t level1[9][11] ={
	{3,0,0,0,0,0,0,0,0,0,0},
	{0,1,2,1,0,1,2,1,0,1,0},
	{0,0,2,0,0,0,2,0,0,0,0},
	{0,1,2,1,0,1,2,1,2,1,0},
	{0,0,2,0,0,2,2,0,0,0,0},
	{0,1,2,1,2,1,0,1,2,1,0},
	{0,0,0,2,2,0,0,0,2,0,2},
	{0,1,0,1,0,1,0,1,2,1,0},
	{0,0,0,0,0,0,0,0,0,0,4}
};

uint8_t level2[9][11] = {
  {3,0,2,2,0,0,0,0,0,2,0},
  {0,1,2,1,0,1,2,1,0,1,2},
  {0,0,0,0,0,0,2,2,0,0,0},
  {0,1,2,1,2,1,2,1,2,1,0},
  {0,0,2,2,0,2,2,2,0,0,0},
  {0,1,2,1,2,1,2,1,0,1,2},
  {0,0,0,2,2,2,0,0,0,2,2},
  {0,1,2,1,2,1,0,1,2,1,2},
  {0,0,0,0,0,0,0,0,0,0,4}
};

Map* MP;
MI0283QT9* lcd;
NunchukLibrary* NC;
GameField* gameField;
WalkingAnimation* WA;
irSend *IRs = new irSend();
irRecv *IRr = new irRecv();
Timer_Display* timer1;

//Verzenden IR
ISR(TIMER2_COMPB_vect)
{
	IRr->setCount(IRr->getCount()+1); //Counter voor het ontvangen.
	IRs->setCount(IRs->getCount()+1); // Counter voor het verzenden.

	if(IRs->getBitSend() == 1 && IRs->getCount() == 13) //Zorg voor +-350 us tussentijd en zet daarna het 38 khz signaal weer op de pin
	{
		if(IRs->getStart()) DDRD |= (1 << PORTD3); //Het enablen van het signaal op de pin
		IRs->setBitSend(0); //Aangeven dat er een bit verzonden mag worden
		IRs->setCount(0); //De counter op 0 zetten
	}

	if((IRs->getCount() == 10) && !(IRs->getBitSend()) && !(IRs->getCurByte())) //Wanneer er geen bits verzonden worden, toch IR signaal blijven verzenden
	{
		DDRD ^= (1 << PORTD3); //38 khz signaal enablen disablen
		IRs->setBitSend(1); // aangeven dat er een bit verzonden, zodat de bovenstaande if 350us wacht tussen de bits.
		IRs->setCount(0); //counter weer op 0
	}

	if(IRs->bombBuffAvail() && !(IRs->getCurByte()) && !(IRs->getBitSend())) //Wanneer iets in de bombbuffer staat. Prio 1
	{
		IRs->setCurByte(IRs->bombFromBuff()); //De byte die verzonden moet worden, wordt uit de verzendbuffer gehaald
		DDRD |= (1 << PORTD3); //signaal wordt op de poort gezet
		IRs->setCount(0); // count weer op 0
		IRs->setSBuf(2); //Hiermee wordt aangegeven uit welke buffer de byte komt en daardoor wordt het juiste startbit verzonden.
	}
	else if(IRs->remainingBuffAvail() && !(IRs->getCurByte()) && !(IRs->getBitSend())) //Wanneer iets in de remaining buffer staat. Prio 2
	{
		IRs->setCurByte(IRs->remainingFromBuff());
		DDRD |= (1 << PORTD3);
		IRs->setCount(0);
		IRs->setSBuf(1);
	}
	else if(IRs->buffAvail() && !(IRs->getCurByte()) && !(IRs->getBitSend())) //Wanneer iets in de buffer staat. Prio 3. 
	{
		IRs->setCurByte(IRs->fromBuff());
		DDRD |= (1 << PORTD3);
		IRs->setCount(0);
		IRs->setSBuf(0);
	}

	if(IRs->getCount() == 34 && !(IRs->getStart()) && IRs->getCurByte() && !(IRs->getSBuf())) //Het verzenden van een startbit voor de normale buffer
	{
		DDRD &= ~(1 << PORTD3);
		IRs->setCount(0);
		IRs->setBitSend(1);
		IRs->setStart(1);
	}
	
	if(IRs->getCount() == 68 && !(IRs->getStart()) && IRs->getCurByte() && (IRs->getSBuf() == 1)) //Het verzenden van een startbit voor de remaining buffer
	{
		DDRD &= ~(1 << PORTD3);
		IRs->setCount(0);
		IRs->setBitSend(1);
		IRs->setStart(1);
	}

	if(IRs->getCount() == 57 && !(IRs->getStart()) && IRs->getCurByte() && (IRs->getSBuf() == 2)) //Het verzenden van een startbit voor de bombbuffer
	{
		DDRD &= ~(1 << PORTD3);
		IRs->setCount(0);
		IRs->setBitSend(1);
		IRs->setStart(1);
	}	

	if(IRs->getStart() && !(IRs->getBitSend()) && IRs->getBitCount() < 16) // Wanneer de 16 bits nog niet verzonden zijn.
	{
		if(IRs->getCount() == 10 && !(1 & (IRs->getCurByte() >> IRs->getBitCount()))) //Het verzenden van een 0
		{
			DDRD &= ~(1 << PORTD3);
			IRs->setCount(0);
			IRs->setBitSend(1);
			IRs->setBitCount(IRs->getBitCount() + 1);
		}
		
		if(IRs->getCount() == 23 && (1 & (IRs->getCurByte() >> IRs->getBitCount()))) //Het verzenden van een 1
		{
			DDRD &= ~(1 << PORTD3);
			IRs->setCount(0);
			IRs->setBitSend(1);
			IRs->setBitCount(IRs->getBitCount() + 1);
			IRs->setParity(IRs->getParity() + 1); //Voor het tellen van het aantal enen voor parity bit
		}
	}
	
	if(IRs->getBitCount() == 16 && !(IRs->getBitSend()) && IRs->getCount() == 46) //verzenden van stopbit
	{
		DDRD &= ~(1 << PORTD3);
		
		IRs->setBitSend(1);
		IRs->setCount(0);

		if((IRs->getParity() & 1)) //Checkt of het aantal enen oneven is. Wanneer dit niet zo is, wordt er nog een stopbit verzonden.
		{
			IRs->setStart(0);
			IRs->setBitCount(0);
			IRs->setCurByte(0);
			IRs->setParity(0);
		}
		else
		{
			IRs->setParity(1);
		}
	}
}

// Ontvangen IR
ISR (INT0_vect)
{
	if(PIND & (1 << PIND2)) // Op de opgaande flank van een bit wordt deze if uitgevoerd
	{
		IRr->setBitTime(IRr->getCount()); // De huidige counter waarde wordt opgeslagen.
			
			if(!(IRr->getStop()) && IRr->getStart()) //Wanneer het startbit ontvangen is en het stopbit nog niet
			{
				if((IRr->getBitTime() >=20) && (IRr->getBitTime() <= 26)) //Als de tijd van een bit tussen 20 en 26 ligt volgens de counter waarde
				{
					IRr->setRcByte(1 << IRr->getRc()); //Er wordt op de juiste plek een 1 geshift.
					IRr->setParity(IRr->getParity() + 1); //Hier wordt ook het aantal enen geteld
				}
				IRr->setRc((IRr->getRc() + 1)); //Hier worden het aantal ontvangen bits bijgehouden
			}

			if(IRr->getStop() == 1) //Als het stopbit ontvangen is
			{
				if(IRr->getParity() & 1) //Als het getal oneven is
				{
					IRr->setStart(0); //Start wordt op 0 0 gezet, zodat er opnieuw een startbit ontvangen kan worden.
					IRr->setRc(0); //Het aantal ontvangen bits wordt op 0 gezet
					IRr->setStop(0); //Het aantal ontvangen stopbits wordt op 0 gezet

					if(IRr->getRcByte()) //Als de ontvangen byte geen 0 is.
					{
						switch(IRr->getSBuf()) //Afhankelijk van welk startbit er verzonden is wordt hier de juiste buffer gekozen
						{
							case 0:
							IRr->toBuff(IRr->getRcByte());
							break;

							case 1:
							IRr->remainingToBuff(IRr->getRcByte());
							break;

							case 2:
							IRr->bombToBuff(IRr->getRcByte());
							break;
						}
					}

					IRr->resetRcByte(); //De ontvangen byte wordt op 0 gezet
					IRr->setParity(0); //Parite (het aantal enen ontvangen) wordt op 0 gezet.
				}
			}

			if(IRr->getStop() == 2) //Als er twee stopbits ontvangen zijn.
			{
				if(!(IRr->getParity() & 1)) //Als het getal even is
				{
					IRr->setStart(0);
					IRr->setRc(0);
					IRr->setStop(0);

					if(IRr->getRcByte())
					{
						switch(IRr->getSBuf())
						{
							case 0:
							IRr->toBuff(IRr->getRcByte());
							break;

							case 1:
							IRr->remainingToBuff(IRr->getRcByte());
							break;

							case 2:
							IRr->bombToBuff(IRr->getRcByte());
							break;
						}
					}

					IRr->resetRcByte();
					IRr->setParity(0);
				}
				else 
				/*Wanneer de parity niet klopt, wordt de waarde niet in de buffer gezet. 
				  Wanneer de parity check niet klopt, kan het zijn dat de volgende byte ook niet in de buffer wordt gezet.
				  De daaropvolgende bits gaan wel goed.*/
				{
					IRr->setStart(0);
					IRr->setRc(0);
					IRr->setStop(0);
					IRr->resetRcByte();
					IRr->setParity(0);
				}
			}		
		
		if((IRr->getBitTime() >=32) && (IRr->getBitTime() <= 38)) //Wanneer een startbit voor de normale buffer ontvangen is.
		{ 
			IRr->setStart((IRr->getStart() + 1));
			IRr->setSBuf(0);
		}

		if((IRr->getBitTime() >=55) && (IRr->getBitTime() <= 61)) //Wanneer een startbit voor de bommenbuffer ontvangen is.
		{
			IRr->setStart((IRr->getStart() + 1));
			IRr->setSBuf(2);
		}

		if((IRr->getBitTime() >=65) && (IRr->getBitTime() <= 71)) //Wanneer een startbit voor de remainingbuffer ontvangen is.
		{			
			IRr->setSBuf(1);
			IRr->setStart((IRr->getStart() + 1));		
		}

		if((IRr->getBitTime() >=44) && (IRr->getBitTime() <= 50)) IRr->setStop((IRr->getStop() + 1)); //Wanneer een stopbit onvangen is.
	}
	else //Op de neergaande flank wordt de counter op 0 gezet
	{
		IRr->setCount(0); //Wanneer het signaal op pin 2 laag wordt, wordt de counter op 0 gezet.
	}
}

int main(void)
{
	IRs->setStart(0);
	IRs->setBitCount(0);
	IRs->setCurByte(0);
	IRs->setParity(0);
	Serial.begin(9600);
	IRs->toBuff(255);

	lcd = new MI0283QT9();
	NC = new NunchukLibrary();
	WA = new WalkingAnimation(lcd);
	lcd->begin();
	Touch touch(lcd);

  setTimer1();

	while(1)
	{
		if(gameStatus == 0)	{
			Menu* menu = new Menu(lcd);
			while(1){
				_delay_ms(10);
				menu->Update();
				if(menu->getStatus() != 0){
					gameStatus = menu->getStatus();
					break;
				}
			}
			delete menu;
		}
		
		if(gameStatus == 1){ 
			timer1 = new Timer_Display();
			SelectLevel();
			Player* playerNC = new Player_NC(MP, 2, NC, IRs);
			Player* playerIR = new Player_IR(MP, 2, IRr);
			gameField = new GameField(lcd, MP, WA, playerNC, playerIR);    
			gameTimer = 1;

			while(1){
				IRs->bombToBuff(291);
				IRs->bombToBuff(290);
				
				if(IRr->bombBuffAvail())
				{
					Serial.println(IRr->bombFromBuff());
				}
				
				NC->ANupdate();
				if(NC->getZButton()){
					if(playerNC->getBomb()){
						gameField->placeBombNC();
					}
				}
				if(playerNC->updatePlayer()){
					gameField->updateGameField_pl_nc();
				}
			}
			return 0;
		}

		if(gameStatus == 2){
			OptionMenu* optMenu = new OptionMenu(lcd);
			while(1){
				optMenu->Update();
				if(optMenu->getStatus() != 2){
					gameStatus = optMenu->getStatus();
					break;
				}
			}
			levelSelect = optMenu->getSelectedLevel();
			delete optMenu;
		}

		if(gameStatus == 3){
		  AfterGame* AG = new AfterGame(lcd, WA, 2000, 300);
		  while(1){
			AG->Update();
			if(AG->getStatus()!=3){
			  gameStatus = AG->getStatus();
			  break;
			}
		  }
		  highscore = AG->getHighScore();
		  delete AG;
		}
    
		if(gameStatus==4){
			SaveHighScore* HS = new SaveHighScore(lcd, highscore);
			while(1){
			  HS->Update();
			  if(HS->getStatus()!=4){
				gameStatus = HS->getStatus();
				break;
			  }
			}
			delete HS;
		}

		if(gameStatus==5){
		  WatchHighScore* WH = new WatchHighScore(lcd);

		  while(1){
			WH->Update();
			if(WH->getStatus()!=5){
			  gameStatus = WH->getStatus();
			  break;
			}
		  }
		  delete WH;
		}
	}
}

void SelectLevel(){
  //levelSelect = getSelectedLevel()
  switch(levelSelect){
    case 1:    MP = new Map(level1); break;
    case 2:    MP = new Map(level2); break;
    default:   MP = new Map(level1); break;
  }
}

void setTimer1()
{
  // initialize timer1 
  cli();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 65015;            // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12)|(0 << CS11)|(1 << CS10);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  sei();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  TCNT1 = 65015;            // preload timer
  OnehzCounter++;

  if(OnehzCounter == 30){
    OnehzCounter = 0;
    if(gameStatus == 1){
      if(timer1->nextSecond()){
        gameStatus = 3; //Game has Ended by the timer
      }
    }
  }
}