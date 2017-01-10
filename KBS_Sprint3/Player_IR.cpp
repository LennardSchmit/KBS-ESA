#ifndef _IRRECV_h
#include "irRecv.h"
#endif
#define SIZE 24
#define STEPOFFSET 2

#include "Player_IR.h"

Player_IR::~Player_IR(){}

bool Player_IR::updatePlayer(){
	
	uint16_t recByte = IRR->fromBuff();						//receive byte
	yPos = recByte & (15 << 0);								//y position
	xPos = (recByte & (15 << 4)) >> 4;						//x position
	if(recByte & (1 << 12)){								//checks if offset is on the x axis
		xStep = ((recByte & (15 << 8)) >> 8) * stepsize;	//sets the correct xStep
		yStep = 0;											//resets the yStep
	} else {
		xStep = 0;											//resets the xStep
		yStep = ((recByte & (15 << 8)) >> 8) * stepsize;	//sets the correct yStep
	}
	status = (recByte & (7 << 13)) >> 13;					//sets the status known as the direction the player was heading
}
