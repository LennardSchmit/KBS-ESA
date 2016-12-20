#include "Player.h"
#include "stdint.h"
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

int Player::getXPx(){
	return xPos * SIZE + xStep;
}

int Player::getYPx(){
	return yPos * SIZE + yStep;
}

int Player::getOldXPx(){
	return oldXPos * SIZE + oldXStep;
}

int Player::getOldYPx(){
	return oldYPos * SIZE + oldYStep;
}
uint8_t Player::getOldXPos(){
	return oldXPos;
}

uint8_t Player::getOldYPos(){
	return oldYPos;
}
int Player::getOldXPosPx(){
	return oldXPos * SIZE;
}

int Player::getOldYPosPx(){
	return oldYPos * SIZE;
}

uint8_t Player::getOldXStep(){
	return oldXStep;
}

uint8_t Player::getOldYStep(){
	return oldYStep;
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
uint8_t Player::getBomb(){
	bombs--;
	return bombs + 1;
}
uint8_t Player::getBombX(){
	if(xStep >= 12){
		return xPos + 1;
		} else {
		return xPos;
	}
}
uint8_t	Player::getBombY(){
	if(yStep >= 12){
		return yPos + 1;
		} else {
		return yPos;
	}
}