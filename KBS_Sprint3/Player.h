#ifndef Player_h
#define Player_h
#include "stdint.h"
//#include "NunchukLibrary.h"
#include "Map.h"

class Player{
	public:

    Player(Map* MP_g, uint8_t bombs_g):MP(MP_g), bombs(3), bombRange(4), life(3), invinsibility(0){}
		virtual ~Player() = 0;
		
		void setPosition(uint8_t xPos_g, uint8_t yPos_g);	//this is called by gamefield to set the location based on the map design in Map.cpp
		
		int getXPx();					//returns the pixel position of X
		int getYPx();					//returns the pixel position of Y
		
		int getOldXPx();					//returns the old pixel position of X
		int getOldYPx();					//returns the old pixel position of Y
		uint8_t getOldXPos();
		uint8_t getOldYPos();
		int getOldXPosPx();
		int getOldYPosPx();
		uint8_t getOldXStep();
		uint8_t getOldYStep();

		void updatePos();				//updates the old position values with the current position values
		
		uint8_t getStatus();
		uint8_t getStepsize();
		uint8_t getBomb();
		void minBomb();
		void plusBomb();
		void updateTotalBlocksDestroyed(uint16_t);
		uint16_t getTotalBlocksDestroyed();
		uint8_t getBombX();
		uint8_t getBombY();		
		uint8_t getBombRange();
		bool checkExplosion(uint8_t x, uint8_t y);
		uint8_t getLife();
		virtual bool updatePlayer();	//updates player positions with the values of the nunchuk

	protected:

		void minLife();
		void toString();
		Map* MP;							
		uint8_t status;						//is the direction the player is heading
		bool statusZero;					//is used for drawing the idle character
		uint8_t bombs;						//is amount of bombs that the player currently has
		uint8_t bombRange;					//is the range of the explosion of a bomb placed by the player
		uint16_t totalBombsPlaced;			//is the amount of bombs placed by the player
		uint16_t totalBlocksDestroyed;		//are the total amount of blocks destroyed by the player
		uint8_t invinsibility;		//player gets after losing a life a short time of invinsibility
		uint8_t life;				//amount of lifes
		uint8_t xPos;				//Position on the X axis range 0 - 10	
		uint8_t yPos;				//Position on the Y axis range 0 - 8
		uint8_t xStep;				//Offset of xPos can range from 0 - 23 if xStep has a value higher than 0 yStep has to be 0 and vice versa
		uint8_t yStep;				//Offset op yPos can range from 0 - 23
		uint8_t oldXPos;			//Is the old position of the xPos is kept for resetting lcd
		uint8_t oldYPos;			//Is the old position of the yPos is kept for resetting lcd
		uint8_t oldXStep;			//is the old position of the xStep is kept for resetting lcd
		uint8_t oldYStep;		    //is the old position of the yStep is kept for resetting lcd
		uint8_t stepsize;			/*is the size the Player is moving, this variable can be changed to every number between 1 - 24 if 0 there will be no movement,
									with the only distriction being that 24 devided by stepsize cannot leave a remainder possible stepsize are:
									1 - 2 - 3 - 4 - 6 - 8 - 12 - 24*/
};

#endif
