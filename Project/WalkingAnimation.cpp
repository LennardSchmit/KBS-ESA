#include "WalkingAnimation.h"
#include <MI0283QT9.h>
#include "Arduino.h"

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
#define RED1    RGB(232, 56, 64)
#define RED2    RGB(176, 16, 24)
#define RED3    RGB(128, 0, 0)

uint8_t Down[8][12] = {
      {0,0,0, 1, 4,3,4, 4, 1,0,0,0}, 
      {0,0,1, 3, 2,2,2, 3, 4,1,0,0},  
      {0,1,1, 6, 5,6,8, 9, 3,1,1,0}, 
      {1,9,7, 5, 5,5,6, 5, 5,7,8,1},  
      {1,9,6, 6, 6,6,9, 6, 6,6,9,1}, 
      {0,1,6,11,13,8,8,13,11,6,1,0},
      {0,1,9,10,12,8,8,12,10,9,1,0},
      {0,0,1, 9, 8,8,8, 8, 9,1,0,0} 
    };
     uint8_t DownStanding[8][12] = {
      {0,1,3,1, 1,9,9,1, 1,4,1,0},
      {1,5,5,4, 3,1,1,4, 3,6,5,1},
      {1,9,6,1, 2,2,2,3, 1,6,9,1}, 
      {1,8,9,0, 3,2,3,3, 1,9,8,1}, 
      {0,1,1,4, 8,8,8,9, 4,1,1,0}, 
      {0,1,6,1, 4,3,3,4, 0,6,1,0}, 
      {0,1,5,6, 1,1,1,1, 6,5,1,0}, 
      {0,0,1,1, 1,0,0,0, 1,1,0,0}, 
    };
     uint8_t DownWalking[8][12] = {
      {0,1,6,1, 1,9,9,1, 1,6,9,1},
      {0,1,5,5, 1,1,1,4, 1,6,5,1},
      {0,1,6,8, 8,1,2,3, 4,1,1,0}, 
      {0,0,1,9, 8,1,3,1, 1,1,1,0}, 
      {0,0,1,1, 1,8,1,5, 5,1,1,0}, 
      {0,0,1,1, 4,3,1,6, 6,5,1,0}, 
      {0,0,0,1, 1,1,1,1, 1,6,1,0}, 
      {0,0,0,0, 0,1,1,1, 1,1,0,0}, 
    };
     uint8_t Sideway[8][12]{
      {0,0,0,1, 1,4,4,1, 1,0,0,0},
      {0,0,1,4, 3,2,2,8, 9,1,1,0},
      {0,1,2,2, 2,3,9,1, 1,5,6,1}, 
      {1,3,4,1, 9,8,1,6, 5,7,6,5}, 
      {4,3,1,8, 1,1,5,5, 6,9,1,1}, 
      {4,4,1,8,8,6,7,11,13,8,1,0}, 
      {1,4,1,9,8,7,7,10,12,8,1,1}, 
      {1,4,1,1, 9,8,7,8, 8,9,1,0}, 
    };
     uint8_t SidewayWalking[8][12]{
      {0,1,1,1, 1,1,9,9, 1,1,0,0},
      {0,1,9,1, 4,1,1,1, 1,1,1,0},
      {0,1,5,1, 3,4,6,5, 5,8,8,1}, 
      {0,0,1,1, 4,3,4,1, 6,9,8,1}, 
      {0,0,1,9, 8,8,8,9, 1,1,1,0}, 
      {0,1,7,1, 1,4,3,4, 1,6,5,1}, 
      {0,1,6,6, 7,1,1,1, 6,5,5,1}, 
      {0,0,1,1, 1,1,1,1, 1,1,1,0}, 
    };
     uint8_t SidewayStanding[8][12]{
      {0,1,0,0, 1,1,9,9, 1,1,0,0},
      {0,0,0,0, 1,3,1,1, 6,1,0,0},
      {0,0,0,0, 1,2,3,7, 5,1,0,0}, 
      {0,0,0,1, 1,3,2,1, 8,8,1,0}, 
      {0,0,0,1, 9,8,8,1, 9,8,1,0}, 
      {0,0,0,0, 1,1,3,2, 1,1,1,0}, 
      {0,0,0,0, 1,7,1,6, 5,5,1,0}, 
      {0,0,0,0, 0,1,1,1, 1,1,0,0}, 
    };
     uint8_t Up[8][12]{
      {0,0,0,0, 0,1,5,6, 1,0,0,0},
      {0,0,0,1, 1,6,5,5, 6,1,0,0},
      {0,1,1,6, 8,8,8,6, 5,1,1,0}, 
      {1,8,1,9, 3,3,3,4, 9,1,8,1}, 
      {0,9,1,4, 1,4,2,3, 1,1,9,1}, 
      {0,1,9,1, 3,3,2,2, 3,1,1,0}, 
      {0,1,1,1, 4,3,3,2, 4,1,1,0}, 
      {0,0,1,7, 1,3,4,3, 1,1,1,0}, 
    };
     uint8_t UpWalking[8][12]{
      {0,1,3,1, 1,1,3,4, 1,7,9,1},
      {1,5,5,4, 3,1,4,4, 1,7,5,1},
      {1,9,5,1, 2,2,1,1, 1,1,1,0}, 
      {1,8,9,1, 3,2,3,3, 9,1,0,0}, 
      {0,1,1,4, 8,8,8,9, 4,1,0,0}, 
      {0,1,7,1, 4,3,4,1, 1,6,1,0}, 
      {0,0,1,1, 1,1,1,6, 5,5,1,0}, 
      {0,0,0,0, 0,0,0,1, 1,1,0,0}, 
    };
    
WalkingAnimation::WalkingAnimation(MI0283QT9* lcd_g, int x, int y){
  mirrorTop = 0;
  mirrorBottom = 0;
  leg = 0;
  lcd = lcd_g;
  drawStanding(x, y, 1);
}

//leg is the feet that is in the air, 0 is right and 1 is left.
void WalkingAnimation::drawCharacter(int x, int y, uint8_t mirrorTop, uint8_t mirrorBottom, uint8_t characterTop[8][12], uint8_t characterBottem[8][12]){
  lcd->fillRect(x-2, y-2, 16, 20 , BACKGROUND);
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

void WalkingAnimation::drawPart(int x, int y, uint8_t part[8][12]){
  if(player==1){
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
  } else if(player==2){
    for(int i = 0; i < 8; i++){
      for(int p = 0; p < 12; p++){
        switch(part[i][p]){
          case 0: lcd->drawPixel((p+x), (i+y), BACKGROUND);   break;
          case 1: lcd->drawPixel((p+x), (i+y), BLACK);   break;
          case 2: lcd->drawPixel((p+x), (i+y), RED1);  break;
          case 3: lcd->drawPixel((p+x), (i+y), RED2);  break;
          case 4: lcd->drawPixel((p+x), (i+y), RED3);  break;
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
}

void WalkingAnimation::drawMirrorPart(int x, int y, uint8_t part[8][12]){
  if(player==1){
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
  } else if(player==2){
    for(uint8_t i = 0; i < 8; i++){
      uint8_t s = 0;
      for(uint8_t p = 11; p < 255; p--){
        switch(part[i][p]){
          case 0: lcd->drawPixel((s+x), (i+y), BACKGROUND);   break;
          case 1: lcd->drawPixel((s+x), (i+y), BLACK);   break;
          case 2: lcd->drawPixel((s+x), (i+y), RED1);  break;
          case 3: lcd->drawPixel((s+x), (i+y), RED2);  break;
          case 4: lcd->drawPixel((s+x), (i+y), RED3);  break;
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

void WalkingAnimation::drawUp(int x, int y, uint8_t selectPlayer){
  player = selectPlayer;
  drawCharacter(x, y, mirrorTop, mirrorBottom, Up, UpWalking);
  mirrorAll();
}

void WalkingAnimation::drawDown(int x, int y, uint8_t selectPlayer){
  player = selectPlayer;
  mirrorTop = 1;
  drawCharacter(x, y, mirrorTop, mirrorBottom, Down, DownWalking);
  mirrorAll();
}

void WalkingAnimation::drawRight(int x, int y, uint8_t selectPlayer){
  player = selectPlayer;
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

void WalkingAnimation::drawLeft(int x, int y, uint8_t selectPlayer){
  player = selectPlayer;
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

void WalkingAnimation::drawStanding(int x, int y, uint8_t selectPlayer){
  player = selectPlayer;
  mirrorTop = 0;
  mirrorBottom = 0;
  drawCharacter(x, y, mirrorTop, mirrorBottom, Down, DownStanding);
}
