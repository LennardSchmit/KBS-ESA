#ifndef WalkingAnimation_h
#define WalkingAnimation_h

#include <MI0283QT9.h>

class WalkingAnimation {
	public:
    WalkingAnimation(MI0283QT9* lcd_g);
		void drawCharacter(uint8_t x, uint8_t y, uint8_t mirrorTop, uint8_t mirrorBottom, uint8_t characterTop[8][12], uint8_t characterBottem[8][12]);
	  void drawPart(uint8_t x, uint8_t y, uint8_t part[8][12]);
    void drawMirrorPart(uint8_t x, uint8_t y, uint8_t part[8][12]);
	  void drawUp(uint8_t x, uint8_t y);
	  void drawDown(uint8_t x, uint8_t y);
    void drawRight(uint8_t x, uint8_t y);
    void drawLeft(uint8_t x, uint8_t y);
    void drawStanding(uint8_t x, uint8_t y);
    void mirrorAll();
	
	private:
  	MI0283QT9* lcd;
  	uint8_t mirrorTop = 0;
  	uint8_t mirrorBottom = 0;
  	uint8_t leg = 0;
  	uint8_t Down[8][12]{
  	  {0,0,0, 1, 4,3,4, 4, 1,0,0,0}, 
  	  {0,0,1, 3, 2,2,2, 3, 4,1,0,0},  
  	  {0,1,1, 6, 5,6,8, 9, 3,1,1,0}, 
  	  {1,9,7, 5, 5,5,6, 5, 5,7,8,1},  
  	  {1,9,6, 6, 6,6,9, 6, 6,6,9,1}, 
  	  {0,1,6,11,13,8,8,13,11,6,1,0},
  	  {0,1,9,10,12,8,8,12,10,9,1,0},
  	  {0,0,1, 9, 8,8,8, 8, 9,1,0,0}, 
  	};
  	uint8_t DownStanding[8][12]{
  	  {0,1,3,1, 1,9,9,1, 1,4,1,0},
  	  {1,5,5,4, 3,1,1,4, 3,6,5,1},
  	  {1,9,6,1, 2,2,2,3, 1,6,9,1}, 
  	  {1,8,9,0, 3,2,3,3, 1,9,8,1}, 
  	  {0,1,1,4, 8,8,8,9, 4,1,1,0}, 
  	  {0,1,6,1, 4,3,3,4, 0,6,1,0}, 
  	  {0,1,5,6, 1,1,1,1, 6,5,1,0}, 
  	  {0,0,1,1, 1,0,0,0, 1,1,0,0}, 
  	};
  	uint8_t DownWalking[8][12]{
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
};

#endif
