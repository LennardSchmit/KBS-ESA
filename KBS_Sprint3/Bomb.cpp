// 
// 
// 

#include "Bomb.h"

Bomb::Bomb(bool thisPlayer_g, uint8_t x_g, uint8_t y_g, uint8_t range_g){
	x = x_g;
	y = y_g;
	range = range_g;
	time = 50;
	thisPlayer = thisPlayer_g;
}
Bomb::~Bomb(){}

boolean Bomb::updateBomb(){
	//Serial.println("minBomb");
	//toString();
	if(time-- == 0){
		return true;
	} else {
		return false;
	}
}
uint8_t Bomb::getX(){
	return x;
}
uint8_t Bomb::getY(){
	return y;
}
uint8_t Bomb::getRange(){
	return range;
}
bool Bomb::updatePlayer(){
	return thisPlayer;
}
void Bomb::toString(){
	Serial.println("Bomb");
	Serial.print("X:\t");
	Serial.print(x);
	Serial.print("\tY:\t");
	Serial.print(y);
	Serial.print("\trange:\t");
	Serial.print(range);
}

