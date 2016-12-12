#include "Player.h"
#include "arduino.h"
#include "Map.h"

#define SIZE 24				//is the size of one block
#define STEPOFFSET 2

Player::~Player(){}

void Player::setPosition(uint8_t xPos_g, uint8_t yPos_g){
	xPos = xPos_g;
	yPos = yPos_g;
	oldXPos = xPos_g;
	oldYPos = xPos_g;
	xStep = 0;
	yStep = 0;
	stepsize = 4;
}

/************************************************************************/
/* Check player.h for information about those functions                 */
/************************************************************************/
int Player::getxPosPx(){
	return xPos * SIZE + xStep;
}
int Player::getyPosPx(){
	return yPos * SIZE + yStep;
}
int Player::getOldXPosPx(){
	return oldXPos * SIZE + oldXStep;
}
int Player::getOldYPosPx(){
	return oldYPos * SIZE + oldYStep;
}
void Player::updatePos(){
	oldXPos = xPos;
	oldYPos = yPos;
	oldXStep = xStep;
	oldYStep = yStep;
}

uint8_t Player::getStatus(){
  return status;
}
