#include "Player_NC.h"
#include <digitalWriteFast.h>
#include <SPI.h>
#include <arduino.h>
#include <MI0283QT9.h>
#include <GraphicsLib.h>
#include "GameField.h"
#include <Wire.h>
#include "NunchukLibrary.h"
#include "Player.h"
#include "Menu.h"
#include "OptionMenu.h"
#include "Touch.h"
#define DEBUG
#define ADDRESS 0x52
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13

uint8_t gameStatus = 1;

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
//Player* playerNC;
GameField* gameField;

volatile uint8_t timer2_counter;    //DIT IS DE TIMER
char tmp[128];

int main(void){
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Start Serial Monitor");
  #endif
 	init();
	MP = new Map(level1);
	lcd = new MI0283QT9();
	NC = new NunchukLibrary();
  lcd->begin();
  Touch touch(lcd);
	
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
      #ifdef DEBUG
      Serial.println("Before Player");
      #endif
			Player* playerNC = new Player_NC(MP, NC);
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

/*
ISR(TIMER2_COMPA_vect)        // interrupt service routine
{
	TCNT2 = timer2_counter;   // preload timer
	cursorMovement();         //Update the location of the player at a certain interfall
}
*/


