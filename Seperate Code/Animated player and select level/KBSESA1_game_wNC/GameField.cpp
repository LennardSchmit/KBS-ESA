/*
 * GameField.cpp
 *
 * Created: 24-11-2016 10:45:28
 *  Author: Rick
 */ 
#include "GameField.h"
#include <arduino.h>
#include "MI0283QT9.h"

#define OUTSIDE		RGB(116, 130, 143) 			//this is the color for the blocks on the outside as well as the blocks that are undestroyable in the game
#define FIELD		RGB(52, 54, 65)		//this is the color for the field you are standing on
#define BLOCK		RGB(194, 91, 86)			//this is the color for the block that are destroyable
//#define PLAYERA		RGB(225, 150, 0) 			
//#define PLAYERB		RGB(122, 186, 122) 		
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13

GameField::GameField(MI0283QT9* lcd_g, Map* mp_g, Player* pl_nc_g){
  lcd = lcd_g;
  mp = mp_g;
  pl_nc = pl_nc_g;
  lcd->fillScreen(OUTSIDE);				//resets the screen
  int leftcornerX = 48;					//is the x-as corner of the block starting by x and y as 0 of the playing field
  int leftcornerY = 13;					//is the y-as corner of the block starting by x and y as 0 of the playing field
  lcd->fillRect( leftcornerX, leftcornerY, 11*SIZE, 9*SIZE, FIELD);

  for(uint8_t y = 0; y < 9; y++)
  {
	  for(uint8_t x = 0; x < 11; x++)			//those loops are looping through the whole playing field
	  {
		  switch(mp->getFieldValue(x, y)){
			  case 1:			//undestroyable block
			  lcd->fillRect( leftcornerX, leftcornerY, SIZE, SIZE, OUTSIDE);
			  break;

			  case 2:			//destroyable block
			  lcd->fillRect( leftcornerX, leftcornerY, SIZE, SIZE, BLOCK);
			  break;

			  case 3:			//player (Nunchuck)
			  WA = new WalkingAnimation(lcd, leftcornerX + 6, leftcornerY + 4);
			  pl_nc->setPosition(x, y);			//update player position so it is able to move
			  mp->setFieldValue(x,y,0);			//update map so the place the player is standing on is 0 needed for updating lcd
			  break;

			  case 4:			//player (received by IRCOM)
        WA->drawStanding(leftcornerX + 6, leftcornerY + 4, 2);
			  //lcd->fillRect(leftcornerX, leftcornerY, SIZE, SIZE, PLAYERB);
			  mp->setFieldValue(x,y,0);			//update map so the place the player is standing on is 0 needed for updating lcd
			  break;
		  }
		  leftcornerX = leftcornerX + SIZE;	//updates the leftcornerX for the next block so the next row can be filled
	  }
	  leftcornerX = OFFSETX;
	  leftcornerY = leftcornerY + SIZE;
  }
}
/************************************************************************/
/* for information about what those functions are doing see GameField.h */
/************************************************************************/
void GameField::updateGameField_pl_nc(){
	lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETX, pl_nc->getOldYPosPx() + OFFSETY, SIZE, SIZE, FIELD);	//draw background
	switch(pl_nc->getStatus()){
	  case 0: WA->drawStanding(pl_nc->getxPosPx()+6 + OFFSETX, pl_nc->getyPosPx()+4 + OFFSETY, 1); break;
    case 1: WA->drawLeft(pl_nc->getxPosPx()+6 + OFFSETX, pl_nc->getyPosPx()+4 + OFFSETY, 1); break;
    case 2: WA->drawRight(pl_nc->getxPosPx()+6 + OFFSETX, pl_nc->getyPosPx()+4 + OFFSETY, 1); break;
    case 3: WA->drawUp(pl_nc->getxPosPx()+6 + OFFSETX, pl_nc->getyPosPx()+4 + OFFSETY, 1); break;
    case 4: WA->drawDown(pl_nc->getxPosPx()+6 + OFFSETX, pl_nc->getyPosPx()+4 + OFFSETY, 1); break;
	}
	pl_nc->updatePos();		//update player so the old position is the current position
}
/*
void GameField::updateGameField_pl_ir(){
  lcd->fillRect(pl_ir->getOldXPosPx() + OFFSETX, pl_ir->getOldYPosPx() + OFFSETY, SIZE, SIZE, FIELD); //draw background
  switch(pl_ir->getStatus()){
    case 0: WA->drawStanding(pl_ir->getxPosPx()+6 + OFFSETX, pl_ir->getyPosPx()+4 + OFFSETY, 2); break;
    case 1: WA->drawLeft(pl_ir->getxPosPx()+6 + OFFSETX, pl_ir->getyPosPx()+4 + OFFSETY, 2); break;
    case 2: WA->drawRight(pl_ir->getxPosPx()+6 + OFFSETX, pl_ir->getyPosPx()+4 + OFFSETY, 2); break;
    case 3: WA->drawUp(pl_ir->getxPosPx()+6 + OFFSETX, pl_ir->getyPosPx()+4 + OFFSETY, 2); break;
    case 4: WA->drawDown(pl_ir->getxPosPx()+6 + OFFSETX, pl_ir->getyPosPx()+4 + OFFSETY, 2); break;
  }
  pl_ir->updatePos();   //update player so the old position is the current position
}
*/
