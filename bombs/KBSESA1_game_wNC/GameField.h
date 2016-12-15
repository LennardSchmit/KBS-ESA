#ifndef GameField_h
#define GameField_h

#include <MI0283QT9.h>
#include "Map.h"
#include "Player.h"
#include "Bomb.h"		//RRR

class GameField {
	public:
		GameField(MI0283QT9* lcd_g, Map* mp_g, Player* pl_nc_g);
		void updateGameField_pl_nc();								//updates player on the lcd and updates the old values of player
		void updateGameField_bomb_nc();								//Checks if bombs need to be placed or exploded. RRR
	private:
    MI0283QT9* lcd;
    Map* mp;
	Player* pl_nc;
};
#endif
