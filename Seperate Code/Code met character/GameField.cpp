/*
 * GameField.cpp
 *
 * Created: 24-11-2016 10:45:28
 *  Author: Rick
 */ 
#include "GameField.h"
#include <arduino.h>
#include "MI0283QT9.h"

#define OUTSIDE		RGB( 116, 130, 143) 			//this is the color for the blocks on the outside as well as the blocks that are undestroyable in the game
#define FIELD		RGB(52, 54, 65)		//this is the color for the field you are standing on
#define BLOCK		RGB(194, 91, 86)			//this is the color for the block that are destroyable
#define PLAYERA		RGB(225, 150, 0) 			
#define PLAYERB		RGB(122, 186, 122) 		
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13
#define DEBUG

//#define BACKGROUND RGB(52, 54, 65)
#define BLACK   RGB(32, 32, 32)     //1
#define GREEN1  RGB(96, 208, 80)    //2
#define GREEN2  RGB(64, 152, 48)    //3
#define GREEN3  RGB(32, 112, 16)    //4
#define BROWN1  RGB(163, 118, 64)   //5
#define BROWN2  RGB(124, 67, 45)    //6
#define BROWN3  RGB(92, 48, 32)     //7
#define YELLOW1 RGB(255, 235, 98)   //8
#define YELLOW2 RGB(222, 164, 30)   //9
#define WHITE1  RGB(255, 255, 255)  //10
#define WHITE2  RGB(220, 220, 220)  //11
#define BLUE1   RGB(128, 160, 192)  //12
#define BLUE2   RGB(64, 96, 128)    //13

//WalkingAnimation WA(lcd);

GameField::GameField(MI0283QT9* lcd_g, Map* mp_g, Player* pl_nc_g){
  lcd = lcd_g;
  mp = mp_g;
  pl_nc = pl_nc_g;
  //WA = new WalkingAnimation(lcd);
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
			  drawStanding(leftcornerX, leftcornerY);
			  //lcd->fillRect(leftcornerX, leftcornerY, SIZE, SIZE, PLAYERA);
			  pl_nc->setPosition(x, y);			//update player position so it is able to move
			  mp->setFieldValue(x,y,0);			//update map so the place the player is standing on is 0 needed for updating lcd
			  break;

			  case 4:			//player (received by IRCOM)
			  lcd->fillRect(leftcornerX, leftcornerY, SIZE, SIZE, PLAYERB);
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
	drawStanding(pl_nc->getxPosPx() + OFFSETX, pl_nc->getyPosPx() + OFFSETY);
	//lcd->fillRect(pl_nc->getxPosPx() + OFFSETX, pl_nc->getyPosPx() + OFFSETY, SIZE, SIZE, PLAYERA);		//draw player
	pl_nc->updatePos();		//update player so the old position is the current position
}

void GameField::drawCharacter(uint8_t x, uint8_t y, uint8_t mirrorTop, uint8_t mirrorBottom, uint8_t characterTop[8][12], uint8_t characterBottem[8][12]){
  lcd->fillRect(x-1, y-1, 14, 18 , FIELD);
  if(!mirrorTop)
  {
    drawPart(x, y, characterTop);
  }
  else if(mirrorTop)
  {
  drawMirrorPart(x, y, characterTop);
  }
  
  y+=8;
  if(!mirrorBottom)
  {
    drawPart(x, y, characterBottem);
  } else if(mirrorBottom)
  {
    drawMirrorPart(x, y, characterBottem);
  }  
}

void GameField::drawPart(uint8_t x, uint8_t y, uint8_t part[8][12]){
  for(int i = 0; i < 8; i++){
    for(int p = 0; p < 12; p++){
      switch(part[i][p]){
        case 0: lcd->drawPixel((p+x), (i+y), FIELD);   break;
        case 1: lcd->drawPixel((p+x), (i+y), BLACK);   break;
        case 2: lcd->drawPixel((p+x), (i+y), GREEN1);  break;
        case 3: lcd->drawPixel((p+x), (i+y), GREEN2);  break;
        case 4: lcd->drawPixel((p+x), (i+y), GREEN3);  break;
        case 5: lcd->drawPixel((p+x), (i+y), BROWN1);  break;
        case 6: lcd->drawPixel((p+x), (i+y), BROWN2);  break;
        case 7: lcd->drawPixel((p+x), (i+y), BROWN3);  break;
        case 8: lcd->drawPixel((p+x), (i+y), YELLOW1); break;
        case 9: lcd->drawPixel((p+x), (i+y), YELLOW2); break;
        case 10:lcd->drawPixel((p+x), (i+y), WHITE1);  break;
        case 11:lcd->drawPixel((p+x), (i+y), WHITE2);  break;
        case 13:lcd->drawPixel((p+x), (i+y), BLUE1);   break;
        case 14:lcd->drawPixel((p+x), (i+y), BLUE2);   break;
      }
    }
  } 
}

void GameField::drawMirrorPart(uint8_t x, uint8_t y, uint8_t part[8][12]){
  for(uint8_t i = 0; i < 8; i++){
    uint8_t s = 0;
    for(uint8_t p = 11; p < 255; p--){
      switch(part[i][p]){
        case 0: lcd->drawPixel((s+x), (i+y), FIELD);   break;
        case 1: lcd->drawPixel((s+x), (i+y), BLACK);   break;
        case 2: lcd->drawPixel((s+x), (i+y), GREEN1);  break;
        case 3: lcd->drawPixel((s+x), (i+y), GREEN2);  break;
        case 4: lcd->drawPixel((s+x), (i+y), GREEN3);  break;
        case 5: lcd->drawPixel((s+x), (i+y), BROWN1);  break;
        case 6: lcd->drawPixel((s+x), (i+y), BROWN2);  break;
        case 7: lcd->drawPixel((s+x), (i+y), BROWN3);  break;
        case 8: lcd->drawPixel((s+x), (i+y), YELLOW1); break;
        case 9: lcd->drawPixel((s+x), (i+y), YELLOW2); break;
        case 10:lcd->drawPixel((s+x), (i+y), WHITE1);  break;
        case 11:lcd->drawPixel((s+x), (i+y), WHITE2);  break;
        case 13:lcd->drawPixel((s+x), (i+y), BLUE1);   break;
        case 14:lcd->drawPixel((s+x), (i+y), BLUE2);   break;
      }
      s++;
    }
  }
}
void GameField::mirrorAll(){
  if(mirrorTop){
    mirrorTop=0;
  } else{
    mirrorTop=1;
  }
  if(mirrorBottom){
    mirrorBottom=0;
  } else{
    mirrorBottom=1;
  }
}

void GameField::drawUp(uint8_t x, uint8_t y){
  drawCharacter(x, y, mirrorTop, mirrorBottom, Up, UpWalking);
  mirrorAll();
}

void GameField::drawDown(uint8_t x, uint8_t y){
  mirrorTop = 1;
  drawCharacter(x, y, mirrorTop, mirrorBottom, Down, DownWalking);
  mirrorAll();
}

void GameField::drawRight(uint8_t x, uint8_t y){
  mirrorTop = 0;
  mirrorBottom = 0;
  if(leg){
    drawCharacter(x, y, mirrorTop, mirrorBottom, Sideway, SidewayWalking);
    leg = 0;
  } else{
    drawCharacter(x, y, mirrorTop, mirrorBottom, Sideway, SidewayStanding);
    leg = 1;
  }
}

void GameField::drawLeft(uint8_t x, uint8_t y){
  mirrorTop = 1;
  mirrorBottom = 1;
  if(leg){
    drawCharacter(x, y, mirrorTop, mirrorBottom, Sideway, SidewayWalking);
    leg = 0;
  } else{
    drawCharacter(x, y, mirrorTop, mirrorBottom, Sideway, SidewayStanding);
    leg = 1;
  }
}

void GameField::drawStanding(uint8_t x, uint8_t y){
  mirrorTop = 0;
  mirrorBottom = 0;
  drawCharacter(x, y, mirrorTop, mirrorBottom, Down, DownStanding);
}
