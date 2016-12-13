#include <digitalWriteFast.h>
#include <SPI.h>
#include <arduino.h>
#include <MI0283QT9.h>
#include "GameField.h"
#include <Wire.h>
#include "NunchukLibrary.h"
#include "Player.h"
#include "Menu.h"
#include "OptionMenu.h"
#include "Touch.h"
#include "irRecv.h"
#include "irSend.h"

#define ADDRESS 0x52
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13

uint8_t gameStatus = 0;

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

Map* MP;
MI0283QT9* lcd;
NunchukLibrary* NC;
Player* playerNC;
GameField* gameField;
irSend *IRs = new irSend();
irRecv *IRr = new irRecv();

ISR(TIMER2_COMPB_vect)
{
	IRr->setCount(IRr->getCount()+1); //Verhoog de count variabele in de klasse irRecv. Hier wordt a mee berekend.
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
	IRs->sendByte(255);
 	//init();
	MP = new Map(level1);
	lcd = new MI0283QT9();
	NC = new NunchukLibrary();
	lcd->begin();
	Touch touch(lcd);
	Serial.begin(9600);
	
	IRs->sendByte(255);
	while(1)
	{
		if(gameStatus == 0)
		{
			Menu* menu = new Menu(lcd);
			while(1)
			{
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
			playerNC = new Player(NC, MP);
			gameField = new GameField(lcd, MP, playerNC);
			while(1){
				NC->ANupdate();
				if(playerNC->updatePlayer()){
					gameField->updateGameField_pl_nc();
				}
			}
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
			delete optMenu;
		}
	}
}


