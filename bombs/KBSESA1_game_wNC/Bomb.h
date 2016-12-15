//RRR
#ifndef Bomb_h
#define Bomb_h
#include "Player.h"
#include "Map.h"

class Bomb
{
	bool explosion;
	
	public:
		Bomb();
		~Bomb();
		void explode();
		void putBomb();
};

#endif 