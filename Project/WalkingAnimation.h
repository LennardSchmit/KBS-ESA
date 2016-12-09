#ifndef WalkingAnimation_h
#define WalkingAnimation_h

#include <MI0283QT9.h>

class WalkingAnimation {
	public:
    WalkingAnimation(MI0283QT9* lcd_g, int x, int y);
		void drawCharacter(int x, int y, uint8_t mirrorTop, uint8_t mirrorBottom, uint8_t characterTop[8][12], uint8_t characterBottem[8][12]);
	  void drawPart(int x, int y, uint8_t part[8][12]);
    void drawMirrorPart(int x, int y, uint8_t part[8][12]);
	  void drawUp(int x, int y);
	  void drawDown(int x, int y);
    void drawRight(int x, int y);
    void drawLeft(int x, int y);
    void drawStanding(int x, int y);
    void mirrorAll();
	
	private:
  	MI0283QT9* lcd;
  	uint8_t mirrorTop;
  	uint8_t mirrorBottom;
  	uint8_t leg;
};

#endif
