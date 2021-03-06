#include <Wire.h>
#include "Player_IR.h"
#include <SPI.h>
#include <stdint.h>
#include <MI0283QT9.h>
#include "GameField.h"
#include "NunchukLibrary.h"
#include "Player_NC.h"
#include "irRecv.h"
#include "irSend.h"
#include "AfterGame.h"
#include "Color.h"
#include "Menu.h"
#include "Touch.h"

/****************************************************/
/* Speler 2 speelt een getrimde versie van de code  */
/* Speler 2 mist:                                   */
/*  - Een normaal start menu                        */
/*  - Highscores opslaan en uitlezen                */
/*  - Een klok die aftelt                           */
/*  - Een optie menu                                */
/****************************************************/

//Als P1 is gedefinieerd dan is het de versie voor speler 1 dit gebeurt in COLOR.H
#ifdef P1
  #include "Menu.h"
  #include "SaveHighScore.h"
  #include "WatchHighScore.h"
  #include "OptionMenu.h"
  #include "Timer_Display.h"
  
  volatile boolean timerUpdate = false;
  uint8_t OnehzCounter = 0;
#endif

//Als p1 niet is gedefinieerd dan is het de versie voor speler 2
#ifndef P1
	volatile uint8_t gameStatus = 6;
#endif
#ifdef P1
	volatile uint8_t gameStatus = 0;
#endif
#define ADDRESS 0x52
#define SIZE 24                  //is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13
volatile uint8_t statusBombPlayer = 1;
uint8_t levelSelect = 1;
int highscore;

//Dit zijn de levels
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
  {3,0,2,2,2,2,2,2,2,2,2},
  {0,1,2,1,2,1,2,1,2,1,2},
  {2,2,2,2,2,2,2,2,2,2,2},
  {2,1,2,1,2,1,2,1,2,1,2},
  {2,2,2,2,2,2,2,2,2,2,2},
  {2,1,2,1,2,1,2,1,2,1,2},
  {2,2,2,2,2,2,2,2,2,2,2},
  {2,1,2,1,2,1,2,1,2,1,0},
  {2,2,2,2,2,2,2,2,2,0,4}
};

Map* MP;
MI0283QT9* lcd;
NunchukLibrary* NC;
GameField* gameField;
WalkingAnimation* WA;
irSend *IRs = new irSend();
irRecv *IRr = new irRecv();
#ifdef P1
Timer_Display* timer1;
#endif

//Verzenden IR
ISR(TIMER2_COMPB_vect)
{
	IRr->setCount(IRr->getCount()+1); //Counter voor het ontvangen.
	IRs->setCount(IRs->getCount()+1); // Counter voor het verzenden.

	if(IRs->getBitSend() == 1 && IRs->getCount() == 13) //Zorg voor +-350(13) us tussentijd en zet daarna het 38 khz signaal weer op de pin
	{
		if(IRs->getStart()) DDRD |= (1 << PORTD3); //Het enablen van het signaal op de pin
		IRs->setBitSend(0); //Aangeven dat er een bit verzonden mag worden
		IRs->setCount(0); //De counter op 0 zetten
	}

	if((IRs->getCount() == 200) && !(IRs->getBitSend()) && !(IRs->getCurByte())) //Wanneer er geen bits verzonden worden, toch IR signaal blijven verzenden
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
	
	if(IRs->getCount() == 102 && !(IRs->getStart()) && IRs->getCurByte() && (IRs->getSBuf() == 1)) //Het verzenden van een startbit voor de remaining buffer
	{
		DDRD &= ~(1 << PORTD3);
		IRs->setCount(0);
		IRs->setBitSend(1);
		IRs->setStart(1);
	}

	if(IRs->getCount() == 68 && !(IRs->getStart()) && IRs->getCurByte() && (IRs->getSBuf() == 2)) //Het verzenden van een startbit voor de bombbuffer
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

		if((IRr->getBitTime() >=65) && (IRr->getBitTime() <= 71)) //Wanneer een startbit voor de bommenbuffer ontvangen is.
		{
			IRr->setStart((IRr->getStart() + 1));
			IRr->setSBuf(2);
		}

		if((IRr->getBitTime() >=98) && (IRr->getBitTime() <= 105)) //Wanneer een startbit voor de remainingbuffer ontvangen is.
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

//hier wordt het level geselecteerd
void SelectLevel()
{
	switch(levelSelect){
		case 1:    MP = new Map(level1); break;
		case 2:    MP = new Map(level2); break;
		default:   MP = new Map(level1); break;
	}
}


int main(void)
{
	IRs->setStart(0);
	IRs->setBitCount(0);
	IRs->setCurByte(0);
	IRs->setParity(0);
  //Serial.begin(9600);
	lcd = new MI0283QT9();
	NC = new NunchukLibrary();
	WA = new WalkingAnimation(lcd);
  Player* playerNC;
  Player* playerIR;
	lcd->begin();

	Touch touch(lcd);

	while(1)
	{
    #ifdef P1
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
		#endif
		if(gameStatus == 1){ 
      #ifdef P1
			timer1 = new Timer_Display();
			setTimer1();
			_delay_ms(10);
			IRs->remainingToBuff(15);
			_delay_ms(10);
			_delay_ms(10);
			IRs->remainingToBuff(15);
			_delay_ms(10);

      #endif
			SelectLevel();
			playerNC = new Player_NC(MP, 2, NC, IRs);
			playerIR = new Player_IR(MP, 2, IRr);
			gameField = new GameField(lcd, MP, WA, IRr, IRs, playerNC, playerIR);    
      
			while(1){	
				if(IRr->bombBuffAvail())
				{
					gameField->placeBombIR();
				}
				if(!(playerNC->getLife())){
					break;
				}
        #ifdef P1
				if(timerUpdate){
					if(timer1->nextSecond()){
						break; //Game has Ended by the timer
					}
					timerUpdate = false;
				}
        #endif
				if(IRr->buffAvail()){
					playerIR->updatePlayer();
					gameField->updateGameField_pl_ir();
				}
				NC->ANupdate();
				if(playerNC->updatePlayer()){
					gameField->updateGameField_pl_nc();
				}

				if(NC->getZButton()){
					if(playerNC->getBomb()){
						gameField->placeBombNC();
					}
				}
				gameField->updateBombs();
			}
			delete MP;
			delete gameField;
      #ifdef P1
			gameStatus = 3;
      #endif
      #ifndef P1
      gameStatus = 6;
      #endif
		}
   
    #ifdef P1
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
    #endif
    
    #ifdef P1
		if(gameStatus == 3){
      //Hier wordt de score van beide spelers na het spel berekend
      //Serial.println(playerNC->getTotalBlocksDestroyed());
      //Serial.println(timer1->getTimeLeft()*25);
      int greenPlayerScore = (playerNC->getTotalBlocksDestroyed()*25) + (playerNC->getLife()*1250) + (timer1->getTimeLeft()*25);
      int redPlayerScore   = (playerIR->getTotalBlocksDestroyed()*25) + (playerIR->getLife()*1250) + (timer1->getTimeLeft()*25);
		  if(greenPlayerScore<redPlayerScore){
        redPlayerScore+=2500;
		  } else if(greenPlayerScore>redPlayerScore){
        greenPlayerScore+=2500;
		  }
      //Die score wordt meegegeven aan het schermpje dat weergegeven wordt.
		  AfterGame* AG = new AfterGame(lcd, WA, greenPlayerScore, redPlayerScore);
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
    #endif
   
    #ifdef P1
		if(gameStatus == 4){
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

		if(gameStatus == 5){
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
    #endif

    //De 2e speler moet wachten tot speler 1 het spel start. Dit werkt soms niet daarom hebben we de knop toegevoegd
    #ifndef P1
    if(gameStatus==6){
      lcd->fillScreen(BACKGROUND);
      lcd->drawText(50, 20, "BOMBERMAN", RED, BACKGROUND, 3);
      lcd->drawText(20, 100, "Please Wait For Player One", RED, BACKGROUND, 2);
      lcd->drawText(50, 130, "Ore Press Button", RED, BACKGROUND, 2);
      lcd->fillRoundRect(60, 190, 200, 40, 10, BLACK);
      lcd->drawText(80, 205, "Start Game", RED, BLACK, 2);
      
      while(1){
        if(IRr->remainingBuffAvail()){
          if(IRr->remainingFromBuff()==15){
            gameStatus=1;
            IRr->remainingFromBuff();
            IRr->remainingFromBuff();
            break;
          }
        }
        lcd->touchRead();
        if(lcd->touchZ()){
          if(lcd->touchY()>190 && lcd->touchY()<230 && lcd->touchX()>60 && lcd->touchX()<260){
            lcd->fillRoundRect(60, 190, 200, 40, 10, RED);
            lcd->drawText(80, 205, "Start Game", BLACK, RED, 2);
            gameStatus = 1;
            break;
          }
        }
      }
    }
    #endif
	}
}

//De timer is voor de klok die aftelt tijdens het spel
#ifdef P1
void setTimer1()
{
  // TIMER 1 for interrupt frequency 1 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 1 Hz increments
  OCR1A = 62499; // = 16000000 / (256 * 1) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 256 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
}

ISR(TIMER1_COMPA_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	timerUpdate = true;
}
#endif
