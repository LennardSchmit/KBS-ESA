#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_
#include "MI0283QT9.h"

class HighScore {
	public:
		HighScore(MI0283QT9* lcd_g, int highscore_g);
		SaveScore(int highscore);
	
	private:
		MI0283QT9* lcd;
		int highscore;
		char letterOne, letterTwo, letterThree;
		
};



#endif /* HIGHSCORE_H_ */