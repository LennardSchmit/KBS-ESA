#ifndef GameField_h
#define GameField_h

#include <MI0283QT9.h>
#include "Map.h"
#include "Player.h"
#include "WalkingAnimation.h"

class GameField {
	public:
		GameField(MI0283QT9* lcd_g, Map* mp_g, WalkingAnimation* WA_g, Player* pl_nc_g, Player* pl_ir_g);
		void updateGameField_pl_nc();								//updates player on the lcd and updates the old values of player
		void updateGameField_pl_ir();
		void placeBombNC();
		void placeBombIR();
	private:
		MI0283QT9* lcd;
		Map* mp;
		Player* pl_nc;
		Player* pl_ir;
		WalkingAnimation* WA;
};
#endif
