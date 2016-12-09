#include "WalkingAnimation.h"
#include <MI0283QT9.h>

#define BACKGROUND RGB(52, 54, 65)
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


WalkingAnimation::WalkingAnimation(MI0283QT9* lcd_g){
  lcd = lcd_g;
}

//leg is the feet that is in the air, 0 is right and 1 is left.
void WalkingAnimation::drawCharacter(uint8_t x, uint8_t y, uint8_t mirrorTop, uint8_t mirrorBottom, uint8_t characterTop[8][12], uint8_t characterBottem[8][12]){
  //lcd->fillRect(x-1, y-1, 14, 18 , BACKGROUND);
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

void WalkingAnimation::drawPart(uint8_t x, uint8_t y, uint8_t part[8][12]){
	for(int i = 0; i < 8; i++){
		for(int p = 0; p < 12; p++){
			switch(part[i][p]){
				case 0: lcd->drawPixel((p+x), (i+y), BACKGROUND);   break;
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

void WalkingAnimation::drawMirrorPart(uint8_t x, uint8_t y, uint8_t part[8][12]){
	for(uint8_t i = 0; i < 8; i++){
		uint8_t s = 0;
		for(uint8_t p = 11; p < 255; p--){
			switch(part[i][p]){
				case 0: lcd->drawPixel((s+x), (i+y), BACKGROUND);   break;
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
void WalkingAnimation::mirrorAll(){
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

void WalkingAnimation::drawUp(uint8_t x, uint8_t y){
  drawCharacter(x, y, mirrorTop, mirrorBottom, Up, UpWalking);
  mirrorAll();
}

void WalkingAnimation::drawDown(uint8_t x, uint8_t y){
  mirrorTop = 1;
  drawCharacter(x, y, mirrorTop, mirrorBottom, Down, DownWalking);
  mirrorAll();
}

void WalkingAnimation::drawRight(uint8_t x, uint8_t y){
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

void WalkingAnimation::drawLeft(uint8_t x, uint8_t y){
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

void WalkingAnimation::drawStanding(uint8_t x, uint8_t y){
  mirrorTop = 0;
  mirrorBottom = 0;
  drawCharacter(x, y, mirrorTop, mirrorBottom, Down, DownStanding);
}

