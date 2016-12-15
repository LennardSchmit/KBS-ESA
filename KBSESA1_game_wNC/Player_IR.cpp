#ifndef _IRRECV_h
#include "irRecv.h"
#endif
#define SIZE 24
#define STEPOFFSET 2

#include "Player_IR.h"

Player_IR::~Player_IR(){}

bool Player_IR::updatePlayer(){
	/*
	ir communication maybe useful but this updatePlayer can be changed
	
	bool error = true;
	uint8_t statusRec = IRR->fromBuff();
	status = ((statusRec & ((1 << 6)|(1 << 5)))>>5);
	if(!status)
		status = 4;
		*/
		
	switch (status)							//switches to the direction the nunchuck is positioned options are left - right - up - down
	{
		case 1:											//LEFT
		if(yStep == 0){								//checks if their is an ability to move up or down because of the offset on the other axis
			if((xStep == 0)){						//checks if the player is entering a new block
				if(!((MP->getFieldValue(xPos - 1, yPos) == 1) || (MP->getFieldValue(xPos - 1, yPos) == 2))){		//checks if the block where the player is moving to can be entered
					if(xPos > 0){					//checks if player is not moving out of the field
						xPos--;						//update position
						xStep = SIZE - stepsize;
						error = false;			//makes sure updatePlayer can give feedback to main about movement
					}
				}
			} else {
				xStep -= stepsize;					//updates step (position)
				error = false;					//makes sure updatePlayer can give feedback to main about movement
			}
		} 
		break;

		case 2:											//RIGHT
		if(yStep == 0){								//checks if their is an ability to move up or down because of the offset on the other axis
			if((xStep == 0)){						//checks if the player is entering a new block
				if(!((MP->getFieldValue(xPos + 1, yPos) == 1) || (MP->getFieldValue(xPos + 1, yPos) == 2))){		//checks if the block where the player is moving to can be entered
					xStep += stepsize;				//updates step (position)
					error = false;				//makes sure updatePlayer can give feedback to main about movement
				}
			} else {
				xStep += stepsize;					//updates step (position)
				if (xStep >= 24) {					//if step update means that player has entered a block without offset
					xStep = 0;						//update position
					xPos++;
				}
				error = false;					//makes sure updatePlayer can give feedback to main about movement
			}
		break;

		case 3:											//UP
		if((xStep == 0)){							//checks if their is an ability to move up or down because of the offset on the other axis
			if(yStep == 0){							//checks if the player is entering a new block
				if(!((MP->getFieldValue(xPos, yPos - 1) == 1) || (MP->getFieldValue(xPos, yPos - 1) == 2))){		//checks if the block where the player is moving to can be entered
					if(yPos > 0){
						yPos--;						//update position
						yStep = SIZE - stepsize;
						error = false;			//makes sure updatePlayer can give feedback to main about movement
					}
				}
				} else {
				yStep -= stepsize;					//updates step (position)
				error = false;					//makes sure updatePlayer can give feedback to main about movement
			}
		} 
		break;

		case 4:											//DOWN
		if((xStep == 0)){								//checks if their is an ability to move up or down because of the offset on the other axis
			if(yStep == 0){							//checks if the player is entering a new block
				if(!((MP->getFieldValue(xPos, yPos + 1) == 1) || (MP->getFieldValue(xPos, yPos + 1) == 2))){		//checks if the block where the player is moving to can be entered
					yStep += stepsize;				//updates step (position)
					error = false;				//makes sure updatePlayer can give feedback to main about movement
				}
			} else {
				yStep += stepsize;					//updates step (position)
				if (yStep >= 24) {					//if step update means that player has entered a block without offset
					yStep = 0;						//update position
					yPos++;
				}
				error = false;					//makes sure updatePlayer can give feedback to main about movement
			}
		} 
		break;
		
	}
	if(!error){
	Serial.println("error");
	}
	return error;
	//is return true if the players position has been updated
}
}
