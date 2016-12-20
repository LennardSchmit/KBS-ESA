#ifndef WalkingAnimation_h
#define WalkingAnimation_h

#include <MI0283QT9.h>

class WalkingAnimation {
	public:
    WalkingAnimation(MI0283QT9* lcd_g);
		void drawCharacter(int x, int y, uint8_t mirrorTop, uint8_t mirrorBottom, uint8_t characterTop[8][12], uint8_t characterBottem[8][12]);
	  void drawPart(int x, int y, uint8_t part[8][12]);
    void drawMirrorPart(int x, int y, uint8_t part[8][12]);
	  void drawUp(int x, int y, uint8_t selectPlayer);
	  void drawDown(int x, int y, uint8_t selectPlayer);
    void drawRight(int x, int y, uint8_t selectPlayer);
    void drawLeft(int x, int y, uint8_t selectPlayer);
    void drawStanding(int x, int y, uint8_t selectPlayer);
    void drawBigStanding(int x, int y, uint8_t selectPlayer);
    void drawPartBig(int x, int y, uint8_t part[8][12]);
    void mirrorAll();
	
	private:
  	MI0283QT9* lcd;
  	uint8_t mirrorTop;
  	uint8_t mirrorBottom;
  	uint8_t leg;
    uint8_t player;
};

#endif
