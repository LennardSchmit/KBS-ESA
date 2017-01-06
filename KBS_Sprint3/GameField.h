#ifndef GameField_h
#define GameField_h

#include <MI0283QT9.h>
#include "Map.h"
#include "Player.h"
#include "WalkingAnimation.h"
#include "irRecv.h"
#include "irSend.h"

class GameField {
	public:
		GameField(MI0283QT9* lcd_g, Map* mp_g, WalkingAnimation* WA_g, irRecv* IRR_g, irSend* IRS_g, Player* pl_nc_g, Player* pl_ir_g);
		void updateGameField_pl_nc();								//updates player on the lcd and updates the old values of player
		void updateGameField_pl_ir();
		void placeBombNC();
		void placeBombIR();
		void updateBombs();
	private:
		void updateBombArray(uint8_t index);
		void explodeBomb(uint8_t index);
		void drawIrPlayer();
		void drawNcPlayer();
		void drawBlock(uint8_t x, uint8_t y, uint16_t xPos, uint16_t yPos);
		uint8_t bombsIndex;
		MI0283QT9* lcd;
		Map* mp;
		irRecv* IRR;
		irSend* IRS;
		Player* pl_nc;
		Player* pl_ir;
		WalkingAnimation* WA;
};
#endif
