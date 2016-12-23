// Bomb.h

#ifndef _BOMB_h
#define _BOMB_h

#include "arduino.h"
#include "Player.h"
class Bomb {
	public:
		Bomb(bool thisPlayer_g, uint8_t x_g, uint8_t y_g, uint8_t bombRange_g);
		~Bomb();
		boolean updateBomb();	
		uint8_t getX();
		uint8_t getY();
		uint8_t getRange();
		bool updatePlayer();
									
	private:
		void toString();
		bool thisPlayer;
		uint8_t x;
		uint8_t y;
		uint8_t range;
		uint8_t time;
};

#endif

