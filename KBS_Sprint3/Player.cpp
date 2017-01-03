#include "Player.h"
#include "stdint.h"
#include "Map.h"

#define SIZE 24				//is the size of one block
#define HALFSIZE SIZE/2
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
uint8_t Player::getStepsize(){
	return stepsize;
}
uint8_t Player::getBomb(){
	return bombs;
}
void Player::minBomb(){
	//Serial.println("--");
	bombs--;
	//Serial.println(bombs);
}
void Player::plusBomb(){
	//Serial.println("++");
	bombs++;
	//Serial.println(bombs);
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
uint8_t Player::getBombRange(){
	return bombRange;
}
uint8_t Player::getLife(){
// 	Serial.print("life:  ");
// 	Serial.println(life);
	return life;
}
void Player::minLife(){
	life--;
	invinsibility = 60;
// 	Serial.print("Ga DOOD:  ");
// 	Serial.println(life);
}
bool Player::checkExplosion(uint8_t x, uint8_t y){
// 	Serial.println("checkExplosion");
// 	Serial.print("x:\t");
// 	Serial.print(x);
// 	Serial.print("y:\t");
// 	Serial.println(y);	
// 	toString();
	if(!invinsibility){
		if(yStep + xStep == 0){
			/*Serial.println("no Offset");*/
			if(x == xPos){
				/*Serial.println("X ECQ");*/
				if(y == yPos){
// 					Serial.println("Y ECQ");
					minLife();
				}
			}
		} else if(xStep == 0){
// 			Serial.println("Y OFFSET");
			if(x == xPos){
// 				Serial.println("X ECQ");
				if(yPos == y && yStep <= HALFSIZE){
					minLife();
				} else if((yPos == (y - 1)) && (yStep >= HALFSIZE)){
					minLife();
				}
			}
		} else if(yStep == 0){
// 			Serial.println("X OFFSET");
			if(y == yPos){
// 				Serial.println("Y ECQ");
				if(xPos == x && xStep <= HALFSIZE){
					minLife();
					} else if((xPos == (x - 1)) && (xStep >= HALFSIZE)){
					minLife();
				}
			}
		}
	}
	/*
	if(yStep == 0 && (xPos == x && xStep <= HALFSIZE) || (xPos - 1 == x, && xStep >= HALFSIZE)){
		
	} else if(yPos == y)
	if(x == bombXPos && y == bombYPos){
		life--;
	}*/
}
void Player::toString(){
// 	Serial.println("Player");
// 	Serial.print("xPos:\t");
// 	Serial.print(xPos);
// 	Serial.print("\tyPos:\t");
// 	Serial.println(yPos);
// 	Serial.print("xStep:\t");
// 	Serial.print(xStep);
// 	Serial.print("\tyStep:\t");
// 	Serial.println(yStep);
}