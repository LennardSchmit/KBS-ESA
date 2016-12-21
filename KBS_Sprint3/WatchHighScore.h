#ifndef WATCHHIGHSCORE_H_
#define WATCHHIGHSCORE_H_
#include "MI0283Qt9.h"

class WatchHighScore {
	public:
		WatchHighScore(MI0283QT9* lcd);
		uint8_t getStatus();
    void Update();
		
	private:
		MI0283QT9* lcd;
    uint8_t status = 5;
};



#endif /* WATCHHIGHSCORE_H_ */
