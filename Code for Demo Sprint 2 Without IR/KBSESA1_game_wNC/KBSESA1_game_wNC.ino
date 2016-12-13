#include "Player_IR.h"
#include <digitalWriteFast.h>
#include <SPI.h>
#include <arduino.h>
#include <MI0283QT9.h>
#include "GameField.h"
#include <Wire.h>
#include "NunchukLibrary.h"
#include "Player_NC.h"
#include "Menu.h"
#include "OptionMenu.h"
#include "Touch.h"
#include "irRecv.h"
#include "irSend.h"
#include "Timer_Display.h"

#define ADDRESS 0x52
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13

uint8_t gameStatus = 0;
uint8_t levelSelect = 1;
uint8_t NCupdate = 0;
uint8_t timeCounter = 0;
uint8_t timeBool = 0;

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
irSend *IRs = new irSend();
irRecv *IRr = new irRecv();

//volatile uint8_t timer2_counter;    //DIT IS DE TIMER
//char tmp[128];

ISR(TIMER2_COMPB_vect)
{
	IRr->setCount(IRr->getCount()+1); //Verhoog de count variabele in de klasse irRecv. Hier wordt a mee berekend.
}

ISR(INT0_vect)
{
	if(PIND & (1 << PIND2))
	{
		IRr->setBitTime(IRr->getCount());
		if(IRr->getStartStop() == 1)
		{
			if((IRr->getBitTime() >=25) && (IRr->getBitTime() <= 35))
			{
				IRr->setRcByte(1 << IRr->getRc());
			}
			IRr->setRc((IRr->getRc() + 1));
		}
		else
		{
			IRr->setStartStop(0);
			IRr->setRc(0);
			IRr->toBuff(IRr->getRcByte());
			IRr->resetRcByte();
		}
		if((IRr->getBitTime() >=38) && (IRr->getBitTime() <= 48)) IRr->setStartStop((IRr->getStartStop() + 1));
	}
	else
	{
		IRr->setCount(0); //Wanner het signaal op pin 2 hoog is wordt de counter op 0 gezet.
	}
}

int main(void){
	IRs->sendByte(255);
	init();
	MP = new Map(level1);
	lcd = new MI0283QT9();
	NC = new NunchukLibrary();
	lcd->begin();
	Touch touch(lcd);
	IRs->sendByte(255);
  Serial.begin(9600);
  setupTimer1();
  
	while(1)
	{
		if(gameStatus == 0)
		{
			Menu* menu = new Menu(lcd);
			while(1)
			{
				_delay_ms(10);
				menu->Update();
				if(menu->getStatus() != 0)
				{
					gameStatus = menu->getStatus();
					break;
				}
			}
			delete menu;
		}
		
		if(gameStatus == 1)
		{
      SelectLevel();
			Player* playerNC = new Player_NC(MP, NC, IRs);
			Player* playerIR = new Player_IR(MP, IRr);
			gameField = new GameField(lcd, MP, playerNC, playerIR);
      Timer_Display* timer1 = new Timer_Display();
      timeBool = 1;
			while(1){
        if(NCupdate == 1){
         NC->ANupdate();
        }
        if(timeBool==2){
          timer1->nextsecond();
          timeBool=1;
        }
				if(playerNC->updatePlayer()){
					gameField->updateGameField_pl_nc();
				}
			}
     timeBool = 0;
			return 0;
		}

		if(gameStatus == 2)
		{
			OptionMenu* optMenu = new OptionMenu(lcd);
			while(1)
			{
				optMenu->Update();
				if(optMenu->getStatus() != 2)
				{
          
					gameStatus = optMenu->getStatus();
					break;
				}
			}
      levelSelect = optMenu->getSelectedLevel();
			delete optMenu;
		}
	}
}

void SelectLevel(){
  switch(levelSelect){
    case 1:    MP = new Map(level1); break;
    case 2:    MP = new Map(level2); break;
    default:   MP = new Map(level1); break;
  }
}
void setupTimer1(){
  // initialize timer1 
  //Serial.begin(9600);
  cli();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 65015;          // preload timer 65536-16MHz/1024/30Hz
  TCCR1B |= (1<<CS22)|(0<<CS21)|(1<<CS20);    // 1024 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  sei();          // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  TCNT1 = 65015;            // preload timer
  Serial.println("HOI");
  
  if(NCupdate==0)NCupdate=1;
  else NCupdate=0;

  timeCounter++;
  if(timeCounter==30){
    timeCounter=0;
    if(timeBool==1){
    timeBool = 2;
    }
  }
}
