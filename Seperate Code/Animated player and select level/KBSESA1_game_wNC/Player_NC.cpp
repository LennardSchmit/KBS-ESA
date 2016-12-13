#ifndef NunchukLibrary_h
#include "NunchukLibrary.h"
#endif	

#define SIZE 24				//is the size of one block
#define STEPOFFSET 2

#include "Player_NC.h"

Player_NC::~Player_NC(){}

bool Player_NC::updatePlayer(){
	bool returnbool = false;
  status = NC->getStatus();
	switch (NC->getStatus())							//switches to the direction the nunchuck is positioned options are left - right - up - down
	{

		case 1:											//LEFT
			if(yStep == 0){								//checks if their is an ability to move up or down because of the offset on the other axis
				if((xStep == 0)){						//checks if the player is entering a new block 
					if(!((MP->getFieldValue(xPos - 1, yPos) == 1) || (MP->getFieldValue(xPos - 1, yPos) == 2))){		//checks if the block where the player is moving to can be entered
						if(xPos > 0){					//checks if player is not moving out of the field
							xPos--;						//update position
							xStep = SIZE - stepsize;
							returnbool = true;			//makes sure updatePlayer can give feedback to main about movement
						}
					}
				} else {
					xStep -= stepsize;					//updates step (position)
					returnbool = true;					//makes sure updatePlayer can give feedback to main about movement
				}
			} else if(yStep <= stepsize * STEPOFFSET){
        yStep -= stepsize;
        returnbool = true; 
        status = 3; 
      } else if(SIZE - yStep <= stepsize * STEPOFFSET){
        yStep += stepsize;
        if(yStep == SIZE){
          yPos++;
          yStep = 0;
        }
        returnbool = true;  
        status = 4;
      }
		break;

		case 2:											//RIGHT
			if(yStep == 0){								//checks if their is an ability to move up or down because of the offset on the other axis
				if((xStep == 0)){						//checks if the player is entering a new block 
					if(!((MP->getFieldValue(xPos + 1, yPos) == 1) || (MP->getFieldValue(xPos + 1, yPos) == 2))){		//checks if the block where the player is moving to can be entered
						xStep += stepsize;				//updates step (position)
						returnbool = true;				//makes sure updatePlayer can give feedback to main about movement
					}
				} else {
					xStep += stepsize;					//updates step (position)
					if (xStep >= 24) {					//if step update means that player has entered a block without offset  
						xStep = 0;						//update position
						xPos++;
					}
					returnbool = true;					//makes sure updatePlayer can give feedback to main about movement
				}
			} else if(yStep <= stepsize * STEPOFFSET){
        yStep -= stepsize;
        returnbool = true;
        status = 3;
      } else if(SIZE - yStep <= stepsize * STEPOFFSET){
        yStep += stepsize;
        if(yStep == SIZE){
          yPos++;
          yStep = 0;
        }
        returnbool = true;
        status = 4;
      }
		break;

		case 3:											//UP
			if((xStep == 0)){							//checks if their is an ability to move up or down because of the offset on the other axis
				if(yStep == 0){							//checks if the player is entering a new block 
					if(!((MP->getFieldValue(xPos, yPos - 1) == 1) || (MP->getFieldValue(xPos, yPos - 1) == 2))){		//checks if the block where the player is moving to can be entered
						if(yPos > 0){
							yPos--;						//update position
							yStep = SIZE - stepsize;
							returnbool = true;			//makes sure updatePlayer can give feedback to main about movement
						}
					}
				} else {
					yStep -= stepsize;					//updates step (position)
					returnbool = true;					//makes sure updatePlayer can give feedback to main about movement
				}
			} else if(xStep <= stepsize * STEPOFFSET){
       xStep -= stepsize;
        returnbool = true;
        status = 1;
      } else if(SIZE - xStep <= stepsize * STEPOFFSET){
        xStep += stepsize;
        if(xStep == SIZE){
          xPos++;
          xStep = 0;
        }
        returnbool = true;
        status = 2;
      }
		break;

		case 4:											//DOWN			
		  if((xStep == 0)){								//checks if their is an ability to move up or down because of the offset on the other axis
				if(yStep == 0){							//checks if the player is entering a new block 
					if(!((MP->getFieldValue(xPos, yPos + 1) == 1) || (MP->getFieldValue(xPos, yPos + 1) == 2))){		//checks if the block where the player is moving to can be entered
						yStep += stepsize;				//updates step (position)
						returnbool = true;				//makes sure updatePlayer can give feedback to main about movement
					}
				} else {
					yStep += stepsize;					//updates step (position)
					if (yStep >= 24) {					//if step update means that player has entered a block without offset 
						yStep = 0;						//update position
						yPos++;
					}
					returnbool = true;					//makes sure updatePlayer can give feedback to main about movement
				}
			} else if(xStep <= stepsize * STEPOFFSET){
       xStep -= stepsize;
        returnbool = true;
        status = 1;
      } else if(SIZE - xStep <= stepsize * STEPOFFSET){
        xStep += stepsize;
        if(xStep == SIZE){
          xPos++;
          xStep = 0;
        }
        returnbool = true;
        status = 2;
      }
		break;
		
	}
	return returnbool;	//is return true if the players position has been updated
}
