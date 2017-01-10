#ifndef NunchukLibrary_h
#include "NunchukLibrary.h"
#endif	
#ifndef _IRRECV_h
#include "irRecv.h"
#endif


#define SIZE 24				//is the size of one block
#define STEPOFFSET 2		//is the number of blocks that the player can be offset of an possible walking direction to correct the nunchuk movement

#include "Player_NC.h"

Player_NC::~Player_NC(){}

bool Player_NC::updatePlayer(){
	if(invinsibility > 0){
		invinsibility--;
	}
	status = 0;
	switch (NC->getStatus())							//switches to the direction the nunchuk is positioned options are left - right - up - down
	{

		case 1:											//LEFT
			if(yStep == 0){								//checks if their is an ability to move left or right because of the offset on the other axis
				if((xStep == 0)){						//checks if the player is entering a new block 
					if(!MP->getFieldValue(xPos - 1, yPos)){		//checks if the block where the player is moving to can be entered
						if(xPos > 0){					//checks if player is not moving out of the field
							xPos--;						//update position
							xStep = SIZE - stepsize;
							status = 1;			//makes sure updatePlayer can give feedback to main about movement
						}
					}
				} else {
					xStep -= stepsize;					//updates step (position)
					status = 1;					//makes sure updatePlayer can give feedback to main about movement
				}
			} else if(yStep <= stepsize * STEPOFFSET){				//checks if the player is a little bit beneath an absolute position
				yStep -= stepsize; 
				status = 3;											//update status for communication
			} else if(SIZE - yStep <= stepsize * STEPOFFSET){		//checks if the player is a little bit above an absolute position
				yStep += stepsize;									//update step
				if(yStep == SIZE){									//checks if player is entering new block
					yPos++;											//update position
					yStep = 0;										
				}
				status = 4;											//update status for communication
			}
		break;

		case 2:											//RIGHT
			if(yStep == 0){								//checks if their is an ability to move left or right because of the offset on the other axis
				if((xStep == 0)){						//checks if the player is entering a new block 
					if(!MP->getFieldValue(xPos + 1, yPos)){		//checks if the block where the player is moving to can be entered
						xStep += stepsize;				//updates step (position)
						status = 2;				//makes sure updatePlayer can give feedback to main about movement
					}
				} else {
					xStep += stepsize;					//updates step (position)
					if (xStep >= 24) {					//if step update means that player has entered a block without offset  
						xStep = 0;						//update position
						xPos++;
					}
					status = 2;					//makes sure updatePlayer can give feedback to main about movement
				}
			} else if(yStep <= stepsize * STEPOFFSET){				//checks if the player is a little bit beneath an absolute position
				yStep -= stepsize;									//update step
				status = 3;											//update status for communication
			} else if(SIZE - yStep <= stepsize * STEPOFFSET){		//checks if the player is a little bit above an absolute position
				yStep += stepsize;									//update step
				if(yStep == SIZE){									//checks if player is entering new block
					yPos++;											//update position
					yStep = 0;
				}
				status = 4;											//update status for communication
			}
		break;

		case 3:														//UP
			if((xStep == 0)){										//checks if their is an ability to move up or down because of the offset on the other axis
				if(yStep == 0){										//checks if the player is entering a new block 
					if(!MP->getFieldValue(xPos, yPos - 1)){		//checks if the block where the player is moving to can be entered
						if(yPos > 0){
							yPos--;									//update position
							yStep = SIZE - stepsize;
							status = 3;						//makes sure updatePlayer can give feedback to main about movement
						}
					}
				} else {
					yStep -= stepsize;								//updates step (position)
					status = 3;								//makes sure updatePlayer can give feedback to main about movement
				}
			} else if(xStep <= stepsize * STEPOFFSET){				//checks if player is a little bit on the left of an absolute position
				xStep -= stepsize;									//update step
				status = 1;											//update status for communication
			} else if(SIZE - xStep <= stepsize * STEPOFFSET){		//checks if player is a little bit on the right of an absolute block
				xStep += stepsize;									//update step
				if(xStep == SIZE){									//checks if player is entering new block
					xPos++;											//update position
					xStep = 0;
				}
				status = 2;											//update status for communication
			}
		break;

		case 4:													//DOWN			
			if((xStep == 0)){									//checks if their is an ability to move up or down because of the offset on the other axis
				if(yStep == 0){									//checks if the player is entering a new block 
					if(!MP->getFieldValue(xPos, yPos + 1)){		//checks if the block where the player is moving to can be entered
						yStep += stepsize;						//updates step (position)
						status = 4;					//makes sure updatePlayer can give feedback to main about movement
					}
				} else {
					yStep += stepsize;					//updates step (position)
					if (yStep >= 24) {					//if step update means that player has entered a block without offset 
						yStep = 0;						//update position
						yPos++;
					}
					status = 4;				//makes sure updatePlayer can give feedback to main about movement
				}
			} else if(xStep <= stepsize * STEPOFFSET){				//checks if player is a little bit on the left of an absolute position
				xStep -= stepsize;									//update step
				status = 1;											//update status for communication
			} else if(SIZE - xStep <= stepsize * STEPOFFSET){		//checks if player is a little bit on the right of an absolute block
				xStep += stepsize;									//update step
				if(xStep == SIZE){									//checks if player is entering new block
					xPos++;											//update position
					xStep = 0;
				}
				status = 2;											//update status for communication
			}
		break;
	}	

	if(status){
		statusZero = true;											//sets true so the player will be drawn on the first time that status == 0
		uint16_t sendData = yPos;									//is the byte for IR with byte 0 - 3 as the y position
		sendData |= xPos << 4;										//sets the IR byte 4 - 7 with the x position
		if(xStep){													//checks if the offset is on the x axis
			sendData |= xStep/stepsize << 8;						//if offset is on x axis the x offset will be set on the 8 - 11 bit of the data
			sendData |= (1 << 12);									//12 bit is set to high so the player ir knows that the offset is on the x axis
		} else {
			sendData |= yStep/stepsize << 8;						//if offset is on y axis the y offset will be set on the 8 - 11 bit of the data
			sendData &= ~(1 << 12);									//12 bit is set to low so the player ir knows that the offset is on the x axis
		}
		sendData |= status << 13;									//the status is the direction the player was going and is set right now it isn't used but could be handy if you were debugging
		IRS->toBuff(sendData);										//send data
		return true;
	} else {
		if(statusZero){												//if player isn't drawn standing still
			statusZero = false;										//sets statusZero so the player will not be redrawn
			return true;											//return true because the player has to be redrawn
		} else {
			return false;											//return false becaus the player is already drawn
		}
	}	
	//is return true if the players position has been updated
}

