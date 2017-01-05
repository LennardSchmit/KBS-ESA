#ifndef _IRRECV_h
#include "irRecv.h"
#endif
#define SIZE 24
#define STEPOFFSET 2

#include "Player_IR.h"

Player_IR::~Player_IR(){}

bool Player_IR::updatePlayer(){
	uint16_t recByte = IRR->fromBuff();
	yPos = recByte & (15 << 0);
	xPos = (recByte & (15 << 4)) >> 4;
	if(recByte & (1 << 12)){
		xStep = (recByte & (15 << 8)) >> 8;
		yStep = 0;
	} else {
		xStep = 0;
		yStep = (recByte & (15 << 8)) >> 8;
	}
	status = (recByte & (7 << 13)) >> 13;
}
