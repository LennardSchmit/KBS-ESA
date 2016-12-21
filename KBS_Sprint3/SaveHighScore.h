#ifndef SAVEHIGHSCORE_H_
#define SAVEHIGHSCORE_H_
#include "MI0283QT9.h"

class SaveHighScore {
	public:
		SaveHighScore(MI0283QT9* lcd_g, int highscore_g);
    void Update();
		void SaveScore();
    uint8_t getStatus();
    unsigned char charMinus(char i);
    unsigned char charPlus(char i);
    bool press;
	
	private:
		MI0283QT9* lcd;
		int highscore;
		unsigned char letterOne, letterTwo, letterThree;
		uint8_t status=4;
};



#endif /* SAVEHIGHSCORE_H_ */
