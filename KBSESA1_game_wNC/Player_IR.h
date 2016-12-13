// Player_IR.h

#ifndef _PLAYER_IR_h
#define _PLAYER_IR_h

#include "Player.h"
#include "irRecv.h"
#include "Map.h"

class Player_IR: public Player{
	public:
	Player_IR(Map* MP_g, irRecv* IRR_g): Player(MP_g),IRR(IRR_g){}
	~Player_IR();
	bool updatePlayer();
	private:
	irRecv* IRR;
};


#endif

