#ifndef AfterGame_H_
#define AfterGame_H_
#include "MI0283QT9.h"
#include "WalkingAnimation.h"

class AfterGame {
  public:
  	AfterGame(MI0283QT9* lcd_g, WalkingAnimation* WA_g, int playerOneScore, int playerTwoScore);
  	void Update();
    uint8_t getStatus();
    int getHighScore();
	
  private:
  	MI0283QT9* lcd;
    WalkingAnimation* WA;
    uint8_t status=3;
    int highScore;
};

#endif /* AfterGame_H_ */
