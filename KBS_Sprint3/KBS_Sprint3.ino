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

uint8_t gameStatus = 3;
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

ISR(TIMER2_COMPB_vect)
{
	
	IRr->setCount(IRr->getCount()+1); //Verhoog de count variabele in de klasse irRecv. Hier wordt a mee berekend.
	IRs->setCount(IRs->getCount()+1);
	/*
	if(IRs->getBitSend() == 1 && IRs->getCount() == 13)
	{
		DDRD |= (1 << PORTD3);
		IRs->setBitSend(0);
	}

	if(IRs->buffAvail() && IRs->getCurByte() == 0)
	{
		IRs->setCurByte(IRs->fromBuff());
		DDRD |= (1 << PORTD3);
		IRs->setCount(0);
	}

	if(IRs->getCount() == 34 && IRs->getStart == 0 && IRs->getBitSend() == 0)
	{
		DDRD &= ~(1 << PORTD3);
		IRs->setCount(0);
		IRs->setBitSend(1);
		IRs->setStart(1);
	}

	if(IRs->getStart() && !(IRs->getBitSend() && IRs->getBitCount() < 15)
	{
		if(IRs->getCount() == 23 && (IRs->getCurByte()) << IRs->getBitCount()))
		{
			DDRD &= ~(1 << PORTD3);
		}
		else if(IRs->getCount() == 10)
		{
			DDRD &= ~(1 << PORTD3);
		}
		IRs->setCount(0);
		IRs->setBitSend(1);
		IRs->setBitCount(IRs->getBitCount() + 1);
    }

	if(IRs->getBitCount() == 15 && IRs->getBitSend() ==0)
	{
		
	}
	*/
}

ISR (INT0_vect)
{
	if(PIND & (1 << PIND2))
	{
		IRr->setBitTime(IRr->getCount());
		if(IRr->getStart() == 1 && IRr->getStop() == 0)
		{
			if((IRr->getBitTime() >=20) && (IRr->getBitTime() <= 30))
			{
				IRr->setRcByte(1 << IRr->getRc());
			}
			IRr->setRc((IRr->getRc() + 1));
		}
		else
		{
			IRr->setStop(0);
			IRr->setStart(0);
			IRr->setRc(0);
			IRr->toBuff(IRr->getRcByte());
			IRr->resetRcByte();
		}
		if((IRr->getBitTime() >=34) && (IRr->getBitTime() <= 44)) IRr->setStart((IRr->getStart() + 1));
		if((IRr->getBitTime() >=47) && (IRr->getBitTime() <= 57)) IRr->setStop((IRr->getStop() + 1));
	}
	else
	{
		IRr->setCount(0); //Wanneer het signaal op pin 2 hoog is wordt de counter op 0 gezet.
	}
}

int main(void){
	lcd = new MI0283QT9();
	NC = new NunchukLibrary();
	WA = new WalkingAnimation(lcd);
	lcd->begin();
	Touch touch(lcd);
	IRs->sendByte(255);
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
