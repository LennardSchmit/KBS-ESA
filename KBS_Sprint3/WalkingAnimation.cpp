#include "WalkingAnimation.h"
#include <MI0283QT9.h>
#include "Arduino.h"
#include "Color.h"

uint8_t destroyableBlock[12][12] = {
  {1,1,1,1,1,1,1,1,1,1,1,1},
  {2,2,2,2,2,1,2,2,2,2,2,1},
  {2,2,2,2,2,1,2,2,2,2,2,1},
  {1,1,1,1,1,1,1,1,1,1,1,1},
  {2,2,1,2,2,2,2,2,1,2,2,2},
  {2,2,1,2,2,2,2,2,1,2,2,2},
  {1,1,1,1,1,1,1,1,1,1,1,1},
  {2,2,2,2,2,1,2,2,2,2,2,1},
  {2,2,2,2,2,1,2,2,2,2,2,1},
  {1,1,1,1,1,1,1,1,1,1,1,1},
  {2,2,1,2,2,2,2,2,1,2,2,2},
  {2,2,1,2,2,2,2,2,1,2,2,2}
};

uint8_t Block[12][12] = {
  {3,1,1,1,1,1,1,1,1,1,1,2},
  {3,3,1,1,1,1,1,1,1,1,2,1},
  {3,3,3,1,1,1,1,1,1,2,1,1},
  {3,3,3,2,2,2,2,2,2,1,1,1},
  {3,3,3,2,2,2,2,2,2,1,1,1},
  {3,3,3,2,2,2,2,2,2,1,1,1},
  {3,3,3,2,2,2,2,2,2,1,1,1},
  {3,3,3,2,2,2,2,2,2,1,1,1},
  {3,3,3,2,2,2,2,2,2,1,1,1},
  {3,3,2,3,3,3,3,3,3,3,1,1},
  {3,2,3,3,3,3,3,3,3,3,3,1},
  {2,3,3,3,3,3,3,3,3,3,3,3}
};

const PROGMEM uint8_t Down[8][12]  = {
      {0,0,0, 1, 4,3,4, 4, 1,0,0,0}, 
      {0,0,1, 3, 2,2,2, 3, 4,1,0,0},  
      {0,1,1, 6, 5,6,8, 9, 3,1,1,0}, 
      {1,9,7, 5, 5,5,6, 5, 5,7,8,1},  
      {1,9,6, 6, 6,6,9, 6, 6,6,9,1}, 
      {0,1,6,11,13,8,8,13,11,6,1,0},
      {0,1,9,10,12,8,8,12,10,9,1,0},
      {0,0,1, 9, 8,8,8, 8, 9,1,0,0} 
    };
    
const PROGMEM uint8_t DownStanding[8][12] = {
      {0,1,3,1, 1,9,9,1, 1,4,1,0},
      {1,5,5,4, 3,1,1,4, 3,6,5,1},
      {1,9,6,1, 2,2,2,3, 1,6,9,1}, 
      {1,8,9,0, 3,2,3,3, 1,9,8,1}, 
      {0,1,1,4, 8,8,8,9, 4,1,1,0}, 
      {0,1,6,1, 4,3,3,4, 0,6,1,0}, 
      {0,1,5,6, 1,1,1,1, 6,5,1,0}, 
      {0,0,1,1, 1,0,0,0, 1,1,0,0}, 
    };
const PROGMEM uint8_t DownWalking[8][12] = {
      {0,1,6,1, 1,9,9,1, 1,6,9,1},
      {0,1,5,5, 1,1,1,4, 1,6,5,1},
      {0,1,6,8, 8,1,2,3, 4,1,1,0}, 
      {0,0,1,9, 8,1,3,1, 1,1,1,0}, 
      {0,0,1,1, 1,8,1,5, 5,1,1,0}, 
      {0,0,1,1, 4,3,1,6, 6,5,1,0}, 
      {0,0,0,1, 1,1,1,1, 1,6,1,0}, 
      {0,0,0,0, 0,1,1,1, 1,1,0,0}, 
    };
const PROGMEM uint8_t Sideway[8][12]{
      {0,0,0,1, 1,4,4,1, 1,0,0,0},
      {0,0,1,4, 3,2,2,8, 9,1,1,0},
      {0,1,2,2, 2,3,9,1, 1,5,6,1}, 
      {1,3,4,1, 9,8,1,6, 5,7,6,5}, 
      {4,3,1,8, 1,1,5,5, 6,9,1,1}, 
      {4,4,1,8,8,6,7,11,13,8,1,0}, 
      {1,4,1,9,8,7,7,10,12,8,1,1}, 
      {1,4,1,1, 9,8,7,8, 8,9,1,0}, 
    };
const PROGMEM uint8_t SidewayWalking[8][12]{
      {0,1,1,1, 1,1,9,9, 1,1,0,0},
      {0,1,9,1, 4,1,1,1, 1,1,1,0},
      {0,1,5,1, 3,4,6,5, 5,8,8,1}, 
      {0,0,1,1, 4,3,4,1, 6,9,8,1}, 
      {0,0,1,9, 8,8,8,9, 1,1,1,0}, 
      {0,1,7,1, 1,4,3,4, 1,6,5,1}, 
      {0,1,6,6, 7,1,1,1, 6,5,5,1}, 
      {0,0,1,1, 1,1,1,1, 1,1,1,0}, 
    };
const PROGMEM uint8_t SidewayStanding[8][12]{
      {0,1,0,0, 1,1,9,9, 1,1,0,0},
      {0,0,0,0, 1,3,1,1, 6,1,0,0},
      {0,0,0,0, 1,2,3,7, 5,1,0,0}, 
      {0,0,0,1, 1,3,2,1, 8,8,1,0}, 
      {0,0,0,1, 9,8,8,1, 9,8,1,0}, 
      {0,0,0,0, 1,1,3,2, 1,1,1,0}, 
      {0,0,0,0, 1,7,1,6, 5,5,1,0}, 
      {0,0,0,0, 0,1,1,1, 1,1,0,0}, 
    };
const PROGMEM uint8_t Up[8][12]{
      {0,0,0,0, 0,1,5,6, 1,0,0,0},
      {0,0,0,1, 1,6,5,5, 6,1,0,0},
      {0,1,1,6, 8,8,8,6, 5,1,1,0}, 
      {1,8,1,9, 3,3,3,4, 9,1,8,1}, 
      {0,9,1,4, 1,4,2,3, 1,1,9,1}, 
      {0,1,9,1, 3,3,2,2, 3,1,1,0}, 
      {0,1,1,1, 4,3,3,2, 4,1,1,0}, 
      {0,0,1,7, 1,3,4,3, 1,1,1,0}, 
    };
const PROGMEM uint8_t UpWalking[8][12]{
      {0,1,3,1, 1,1,3,4, 1,7,9,1},
      {1,5,5,4, 3,1,4,4, 1,7,5,1},
      {1,9,5,1, 2,2,1,1, 1,1,1,0}, 
      {1,8,9,1, 3,2,3,3, 9,1,0,0}, 
      {0,1,1,4, 8,8,8,9, 4,1,0,0}, 
      {0,1,7,1, 4,3,4,1, 1,6,1,0}, 
      {0,0,1,1, 1,1,1,6, 5,5,1,0}, 
      {0,0,0,0, 0,0,0,1, 1,1,0,0}, 
    };

uint8_t offset[16] = {2, 1, 1, 0, 0, 0, 1, 1, 2, 4, 5, 7, 9, 11, 10, 14};


uint8_t lineOne[3]      =       {1, 1, 1};
uint8_t lineTwo[6]      =    {1, 4, 2, 3, 1, 1};
uint8_t lineThree[8]    =    {1, 3, 2, 2, 4, 4, 1, 1};
uint8_t lineFour[11]    = {1, 4, 3, 3, 2, 2, 2, 4, 4, 1, 1};
uint8_t lineFive[13]    = {1, 4, 3, 3, 3, 3, 2, 2, 2, 4, 4, 1, 1};
uint8_t lineSix[17]     = {1, 4, 3, 3, 3, 3, 3, 2, 2, 2, 4, 4, 1, 1, 1, 0,14};
uint8_t lineSeven[20]   =    {1, 4, 3, 3, 3, 3, 3, 3, 2, 2, 2,14, 4,15, 1, 1, 0, 0, 0,14};
uint8_t lineEight[20]   =    {1, 4, 4, 4, 3, 3, 3, 3, 3, 9, 2, 9, 2, 2, 8, 9, 1, 0,15, 9};
uint8_t lineNine[17]    =       {1, 1, 4, 4, 4, 3, 3, 3,15, 2, 2, 2,14,11,11,18, 9};
uint8_t lineTen[16]     =             {1, 1, 4, 4, 3, 3, 3, 2, 8,18, 9,17,15,18, 1, 8};
uint8_t lineEleven[15]  =                {1, 1, 4, 4,15, 3, 9, 3,14,17, 1,18,17, 1,14};
uint8_t lineTwelve[13]  =                      {1, 1, 1, 4,15,18,17,17,17,17,17, 1,15};
uint8_t lineThirteen[10]=                            {1, 1, 9,18,18, 9,10,18, 1, 9};
uint8_t lineFourteen[10]=                                  {1,18,14,18,18, 8, 1, 0,14, 9};
uint8_t lineFifteen[7]  =                              {14,0, 9, 1, 1, 8,16};
uint8_t lineSixteen[3]  =                                         {15, 0, 9};

WalkingAnimation::WalkingAnimation(MI0283QT9* lcd_g){
  mirrorTop = 0;
  mirrorBottom = 0;
  leg = 0;
  lcd = lcd_g;
}

//leg is the feet that is in the air, 0 is right and 1 is left.
void WalkingAnimation::drawCharacter(int x, int y, uint8_t mirrorTop, uint8_t mirrorBottom, uint8_t characterTop[8][12], uint8_t characterBottem[8][12]){
  lcd->fillRect(x-2, y-2, 16, 20 , BLACK);
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
        switch(pgm_read_byte(&part[i][p])){
  				case 0: lcd->drawPixel((p+x), (i+y), BLACK);   break;
  				case 1: lcd->drawPixel((p+x), (i+y), PLAYERBLACK);   break;
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
        switch(pgm_read_byte(&part[i][p])){
          case 0: lcd->drawPixel((p+x), (i+y), BLACK);   break;
          case 1: lcd->drawPixel((p+x), (i+y), PLAYERBLACK);   break;
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
  			switch(pgm_read_byte(&part[i][p])){
  				case 0: lcd->drawPixel((s+x), (i+y), BLACK);   break;
  				case 1: lcd->drawPixel((s+x), (i+y), PLAYERBLACK);   break;
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
        switch(pgm_read_byte(&part[i][p])){
          case 0: lcd->drawPixel((s+x), (i+y), BLACK);   break;
          case 1: lcd->drawPixel((s+x), (i+y), PLAYERBLACK);   break;
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

void WalkingAnimation::drawBigStanding(int x, int y, uint8_t selectPlayer){
  player = selectPlayer;
  drawPartBig(x, y, Down);
  y+=24;
  drawPartBig(x, y, DownStanding);
}

void WalkingAnimation::drawPartBig(int x, int y, uint8_t part[8][12]){
  if(player==1){
    for(int i = 0; i < 24; i+=3){
      for(int p = 0; p < 32; p+=3){
        switch(pgm_read_byte(&part[(i/3)][(p/3)])){
          case 0: lcd->fillRect((p+x), (i+y), 3, 3, BLACK);  break;
          case 1: lcd->fillRect((p+x), (i+y), 3, 3, PLAYERBLACK);   break;
          case 2: lcd->fillRect((p+x), (i+y), 3, 3, GREEN1);  break;
          case 3: lcd->fillRect((p+x), (i+y), 3, 3, GREEN2);  break;
          case 4: lcd->fillRect((p+x), (i+y), 3, 3, GREEN3);  break;
          case 5: lcd->fillRect((p+x), (i+y), 3, 3, BROWN1);  break;
          case 6: lcd->fillRect((p+x), (i+y), 3, 3, BROWN2);  break;
          case 7: lcd->fillRect((p+x), (i+y), 3, 3, BROWN3);  break;
          case 8: lcd->fillRect((p+x), (i+y), 3, 3, YELLOW1); break;
          case 9: lcd->fillRect((p+x), (i+y), 3, 3, YELLOW2); break;
          case 10:lcd->fillRect((p+x), (i+y), 3, 3, WHITE1);  break;
          case 11:lcd->fillRect((p+x), (i+y), 3, 3, WHITE2);  break;
          case 13:lcd->fillRect((p+x), (i+y), 3, 3, BLUE1);   break;
          case 14:lcd->fillRect((p+x), (i+y), 3, 3, BLUE2);   break;
        }
      }
    } 
  } 
  
  else if(player==2){
    for(int i = 0; i < 24; i+=3){
      for(int p = 0; p < 32; p+=3){
        switch(pgm_read_byte(&part[(i/3)][(p/3)])){
          case 0: lcd->fillRect((p+x), (i+y), 3, 3, BLACK);  break;
          case 1: lcd->fillRect((p+x), (i+y), 3, 3, PLAYERBLACK);   break;
          case 2: lcd->fillRect((p+x), (i+y), 3, 3, RED1);  break;
          case 3: lcd->fillRect((p+x), (i+y), 3, 3, RED2);  break;
          case 4: lcd->fillRect((p+x), (i+y), 3, 3, RED3);  break;
          case 5: lcd->fillRect((p+x), (i+y), 3, 3, BROWN1);  break;
          case 6: lcd->fillRect((p+x), (i+y), 3, 3, BROWN2);  break;
          case 7: lcd->fillRect((p+x), (i+y), 3, 3, BROWN3);  break;
          case 8: lcd->fillRect((p+x), (i+y), 3, 3, YELLOW1); break;
          case 9: lcd->fillRect((p+x), (i+y), 3, 3, YELLOW2); break;
          case 10:lcd->fillRect((p+x), (i+y), 3, 3, WHITE1);  break;
          case 11:lcd->fillRect((p+x), (i+y), 3, 3, WHITE2);  break;
          case 13:lcd->fillRect((p+x), (i+y), 3, 3, BLUE1);   break;
          case 14:lcd->fillRect((p+x), (i+y), 3, 3, BLUE2);   break;
        }
      }
    }
  }
}

void WalkingAnimation::drawBomb(int x, int y, uint8_t selectPlayer){
  uint8_t *line;
  for(uint8_t i = 0; i < 16; i++){
    uint8_t size;
    switch(i){
      case 0:  line = lineOne;     size =3;  break;
      case 1:  line = lineTwo;     size =6;  break;
      case 2:  line = lineThree;   size =8;  break;
      case 3:  line = lineFour;    size =11;  break;
      case 4:  line = lineFive;    size =13;  break;
      case 5:  line = lineSix;     size =17;  break;
      case 6:  line = lineSeven;   size =20;  break;
      case 7:  line = lineEight;   size =20;  break;
      case 8:  line = lineNine;    size =17;  break;
      case 9:  line = lineTen;     size =16;  break;
      case 10: line = lineEleven;  size =15;  break;
      case 11: line = lineTwelve;  size =13;  break;
      case 12: line = lineThirteen;size =10;  break;
      case 13: line = lineFourteen;size =10;  break;
      case 14: line = lineFifteen; size =7;  break;
      case 15: line = lineSixteen; size =3;  break;
    }
    for(uint8_t j = 0; j < size; j++){
      if(selectPlayer ==1){
      switch(line[j]){
          //case 0: lcd->drawPixel((j+x+offset[i]), (i+y), );   break;
          case 1: lcd->drawPixel((j+x+offset[i]), (i+y), PLAYERBLACK);   break;
          case 2: lcd->drawPixel((j+x+offset[i]), (i+y), GREEN1);  break;
          case 3: lcd->drawPixel((j+x+offset[i]), (i+y), GREEN2);  break;
          case 4: lcd->drawPixel((j+x+offset[i]), (i+y), GREEN3);  break;
          case 8: lcd->drawPixel((j+x+offset[i]), (i+y), YELLOW1); break;
          case 9: lcd->drawPixel((j+x+offset[i]), (i+y), YELLOW2); break;
          case 11:lcd->drawPixel((j+x+offset[i]), (i+y), WHITE2);  break;
          case 14:lcd->drawPixel((j+x+offset[i]), (i+y), RED1);    break;
          case 15:lcd->drawPixel((j+x+offset[i]), (i+y), RED2);    break;
          case 16:lcd->drawPixel((j+x+offset[i]), (i+y), ORANGE1);    break;
          case 17:lcd->drawPixel((j+x+offset[i]), (i+y), GREY1);  break;
          case 18:lcd->drawPixel((j+x+offset[i]), (i+y), GREY2);   break;
        }
      } else if(selectPlayer==2){
        switch(line[j]){
          //case 0: lcd->drawPixel((j+x+offset[i]), (i+y), );   break;
          case 1: lcd->drawPixel((j+x+offset[i]), (i+y), PLAYERBLACK);   break;
          case 2: lcd->drawPixel((j+x+offset[i]), (i+y), RED1);  break;
          case 3: lcd->drawPixel((j+x+offset[i]), (i+y), RED2);  break;
          case 4: lcd->drawPixel((j+x+offset[i]), (i+y), RED3);  break;
          case 8: lcd->drawPixel((j+x+offset[i]), (i+y), YELLOW1); break;
          case 9: lcd->drawPixel((j+x+offset[i]), (i+y), YELLOW2); break;
          case 11:lcd->drawPixel((j+x+offset[i]), (i+y), WHITE2);  break;
          case 14:lcd->drawPixel((j+x+offset[i]), (i+y), RED1);    break;
          case 15:lcd->drawPixel((j+x+offset[i]), (i+y), YELLOW1);    break;
          case 16:lcd->drawPixel((j+x+offset[i]), (i+y), ORANGE1);    break;
          case 17:lcd->drawPixel((j+x+offset[i]), (i+y), GREY1);  break;
          case 18:lcd->drawPixel((j+x+offset[i]), (i+y), GREY2);   break;
        }
      }
    }
  }
  delete[]line;
}

void WalkingAnimation::drawBlock(int x, int y, uint8_t selectBlock){
  if(selectBlock==0){
    for(int i = 0; i < 24; i+=2){
        for(int p = 0; p < 24; p+=2){
          switch(destroyableBlock[i/2][p/ 2]){
            case 0: lcd->fillRect((p+x), (i+y), 2, 2, BLACK);  break;
            case 1: lcd->fillRect((p+x), (i+y), 2, 2, PLAYERBLACK);   break;
            case 2: lcd->fillRect((p+x), (i+y), 2, 2, RED);  break;
          }
        }
      }
  } else if(selectBlock==1){
    for(int i = 0; i < 24; i+=2){
        for(int p = 0; p < 24; p+=2){
          switch(Block[i/2][p/ 2]){
            case 1: lcd->fillRect((p+x), (i+y), 2, 2, BACKGROUND);  break;
            case 2: lcd->fillRect((p+x), (i+y), 2, 2, BLACK);   break;
            case 3: lcd->fillRect((p+x), (i+y), 2, 2, PLAYERBLACK);  break;
          }
        }
      }
  }
}

