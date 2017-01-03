#include "GameField.h"
#include <stdint.h>
#include "MI0283QT9.h"
#include "Color.h"
		
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13

GameField::GameField(MI0283QT9* lcd_g, Map* mp_g, WalkingAnimation* WA_g, Player* pl_nc_g, Player* pl_ir_g){
	lcd = lcd_g;
	mp = mp_g;
	pl_nc = pl_nc_g;
	pl_ir = pl_ir_g;
	WA = WA_g;
	lcd->fillScreen(BACKGROUND);				//resets the screen
	int leftcornerX = 48;					//is the x-as corner of the block starting by x and y as 0 of the playing field
	int leftcornerY = 13;					//is the y-as corner of the block starting by x and y as 0 of the playing field
	lcd->fillRect( leftcornerX, leftcornerY, 11*SIZE, 9*SIZE, BLACK);

	for(uint8_t y = 0; y < 9; y++)
	{
		for(uint8_t x = 0; x < 11; x++)			//those loops are looping through the whole playing field
		{
			switch(mp->getFieldValue(x, y)){
				case 1:			//undestroyable block
					WA->drawBlock(leftcornerX, leftcornerY, 1);
				break;

				case 2:			//destroyable block
					WA->drawBlock(leftcornerX, leftcornerY, 0);
				break;

				case 3:			//player (Nunchuck)
					WA->drawStanding(leftcornerX + 6, leftcornerY + 4, 1);
					pl_nc->setPosition(x, y);			//update player position so it is able to move
					mp->setFieldValue(x,y,0);			//update map so the place the player is standing on is 0 needed for updating lcd
				break;

				case 4:			//player (received by IRCOM)
					WA->drawStanding(leftcornerX + 6, leftcornerY + 4, 2);
					pl_ir->setPosition(x, y);
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

	if(pl_nc->getOldXStep()){
		if(mp->getFieldValue((pl_nc->getOldXPos() + 1), pl_nc->getOldYPos()) == 0){
			lcd->fillRect(pl_nc->getOldXPosPx() + SIZE + OFFSETX, pl_nc->getOldYPosPx() + OFFSETY, SIZE, SIZE, BLACK);
		} else if(mp->getFieldValue(pl_nc->getOldXPos() + 1, pl_nc->getOldYPos()) >= 5){
			lcd->fillRect(pl_nc->getOldXPosPx() + SIZE + OFFSETX, pl_nc->getOldYPosPx() + OFFSETY, SIZE, SIZE, RED2);
		}
	}

	if(pl_nc->getOldYStep()){
		if(mp->getFieldValue(pl_nc->getOldXPos(), (pl_nc->getOldYPos() + 1)) == 0){
			lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETX, pl_nc->getOldYPosPx() + SIZE + OFFSETY, SIZE, SIZE, BLACK);
		} else if(mp->getFieldValue(pl_nc->getOldXPos(), (pl_nc->getOldYPos() + 1)) >= 5){
			lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETX, pl_nc->getOldYPosPx() + SIZE + OFFSETY, SIZE, SIZE, RED2);
		}
	}

	if(mp->getFieldValue(pl_nc->getOldXPos(), pl_nc->getOldYPos()) == 0){
		lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETX, pl_nc->getOldYPosPx() + OFFSETY, SIZE, SIZE, BLACK);
	} else if(mp->getFieldValue(pl_nc->getOldXPos(), pl_nc->getOldYPos()) >= 5){
		lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETX, pl_nc->getOldYPosPx() + OFFSETY, SIZE, SIZE, RED2);
	}

	switch(pl_nc->getStatus()){
		case 0: WA->drawStanding(pl_nc->getXPx()+6 + OFFSETX, pl_nc->getYPx()+4 + OFFSETY, 1); break;
		case 1: WA->drawLeft(pl_nc->getXPx()+6 + OFFSETX, pl_nc->getYPx()+4 + OFFSETY, 1); break;
		case 2: WA->drawRight(pl_nc->getXPx()+6 + OFFSETX, pl_nc->getYPx()+4 + OFFSETY, 1); break;
		case 3: WA->drawUp(pl_nc->getXPx()+6 + OFFSETX, pl_nc->getYPx()+4 + OFFSETY, 1); break;
		case 4: WA->drawDown(pl_nc->getXPx()+6 + OFFSETX, pl_nc->getYPx()+4 + OFFSETY, 1); break;
	}
	pl_nc->updatePos();		//update player so the old position is the current position
}

void GameField::updateGameField_pl_ir(){
  lcd->fillRect(pl_ir->getOldXPx() + OFFSETX, pl_ir->getOldYPx() + OFFSETY, SIZE, SIZE, BLACK); //draw background
  switch(pl_ir->getStatus()){
    case 0: WA->drawStanding(pl_ir->getXPx()+6 + OFFSETX, pl_ir->getYPx()+4 + OFFSETY, 2); break;
    case 1: WA->drawLeft(pl_ir->getXPx()+6 + OFFSETX, pl_ir->getYPx()+4 + OFFSETY, 2); break;
    case 2: WA->drawRight(pl_ir->getXPx()+6 + OFFSETX, pl_ir->getYPx()+4 + OFFSETY, 2); break;
    case 3: WA->drawUp(pl_ir->getXPx()+6 + OFFSETX, pl_ir->getYPx()+4 + OFFSETY, 2); break;
    case 4: WA->drawDown(pl_ir->getXPx()+6 + OFFSETX, pl_ir->getYPx()+4 + OFFSETY, 2); break;
  }
  pl_ir->updatePos();   //update player so the old position is the current position
}

void GameField::placeBombNC(){
	mp->setFieldValue(pl_nc->getBombX(), pl_nc->getBombY(), 5);
	lcd->fillRect(pl_nc->getBombX() * SIZE + OFFSETX, pl_nc->getBombY() * SIZE + OFFSETY, SIZE, SIZE, RED2);
	switch(pl_nc->getStatus()){
		case 0: WA->drawStanding(pl_nc->getXPx()+6 + OFFSETX, pl_nc->getYPx()+4 + OFFSETY, 1); break;
		case 1: WA->drawLeft(pl_nc->getXPx()+6 + OFFSETX, pl_nc->getYPx()+4 + OFFSETY, 1); break;
		case 2: WA->drawRight(pl_nc->getXPx()+6 + OFFSETX, pl_nc->getYPx()+4 + OFFSETY, 1); break;
		case 3: WA->drawUp(pl_nc->getXPx()+6 + OFFSETX, pl_nc->getYPx()+4 + OFFSETY, 1); break;
		case 4: WA->drawDown(pl_nc->getXPx()+6 + OFFSETX, pl_nc->getYPx()+4 + OFFSETY, 1); break;
	}
}

void GameField::placeBombIR(){

}
