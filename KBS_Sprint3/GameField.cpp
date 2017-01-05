#include "GameField.h"
#include <stdint.h>
#include "MI0283QT9.h"
#include "Color.h"
#include "Bomb.h"
#define SIZE 24									//is the amount of pixels of on BACKGROUND the game has 9 (y) by 11 (x) BACKGROUNDs and is 216 by 264 px.
#define OFFSETX 48
#define OFFPPLAYER
#define OFFSETXPLAYER OFFSETX + 6
#define OFFSETXSIZE OFFSETX + SIZE
#define OFFSETY 13
#define OFFSETYPLAYER OFFSETY + 4
#define OFFSETYSIZE OFFSETY + SIZE

Bomb* bombs[14] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};


GameField::GameField(MI0283QT9* lcd_g, Map* mp_g, WalkingAnimation* WA_g, irRecv* IRR_g, irSend* IRS_g, Player* pl_nc_g, Player* pl_ir_g){
	lcd = lcd_g;
	mp = mp_g;
	WA = WA_g;
	IRR = IRR_g;
	IRS = IRS_g;
	pl_nc = pl_nc_g;
	pl_ir = pl_ir_g;

	for(int i = 0; i < 10; i++){
		bombs[i] = NULL;
	}
	bombsIndex = 0;

	lcd->fillScreen(BACKGROUND);				//resets the screen
	int leftcornerX = OFFSETX;					//is the x-as corner of the block starting by x and y as 0 of the playing field
	int leftcornerY = OFFSETY;					//is the y-as corner of the block starting by x and y as 0 of the playing field
	lcd->fillRect( leftcornerX, leftcornerY, 11*SIZE, 9*SIZE, BLACK);

	for(uint8_t y = 0; y < 9; y++)
	{
		for(uint8_t x = 0; x < 11; x++)			//those loops are looping through the whole playing field
		{
			switch(mp->getFieldValue(x, y)){
				case 1:			//undestroyable block
					WA->drawBlock(leftcornerX, leftcornerY, 1);
					//lcd->fillRect(leftcornerX, leftcornerY, SIZE, SIZE, BACKGROUND);
				break;

				case 2:			//destroyable block
					WA->drawBlock(leftcornerX, leftcornerY, 0);
					//lcd->fillRect(leftcornerX, leftcornerY, SIZE, SIZE, RED);
				break;

				case 3:			//player (Nunchuck)
					WA->drawStanding(leftcornerX + 6, leftcornerY + 4, 1);
					pl_nc->setPosition(x, y);			//update player position so it is able to move
					mp->setFieldValue(x,y,0);			//update map so the place the player is standing on is 0 needed for updating lcd
				break;

				case 4:			//player (received by IRCOM)
					//WA->drawStanding(leftcornerX + 6, leftcornerX + 4, 2);
					lcd->fillRect(leftcornerX, leftcornerY, SIZE, SIZE, RED2);
					pl_ir->setPosition(x, y);
					mp->setFieldValue(x,y,0);			//update map so the place the player is standing on is 0 needed for updating lcd
				break;
			}
			leftcornerX = leftcornerX + SIZE;	//updates the leftcornerX for the next block so the next row can be filled
		}
		leftcornerX = OFFSETX;
		leftcornerY = leftcornerY + SIZE;
	}
}

/************************************************************************/
/* for information about what those functions are doing see GameField.h */
/************************************************************************/
void GameField::updateGameField_pl_nc(){

	if(pl_nc->getOldXStep()){
		if(mp->getFieldValue((pl_nc->getOldXPos() + 1), pl_nc->getOldYPos()) == 0){
			lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETXSIZE, pl_nc->getOldYPosPx() + OFFSETY, SIZE, SIZE, BLACK);
		} else if(mp->getFieldValue(pl_nc->getOldXPos() + 1, pl_nc->getOldYPos()) >= 5){
			lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETXSIZE, pl_nc->getOldYPosPx() + OFFSETY, SIZE, SIZE, RED2);
		}
	}

	if(pl_nc->getOldYStep()){
		if(mp->getFieldValue(pl_nc->getOldXPos(), (pl_nc->getOldYPos() + 1)) == 0){
			lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETX, pl_nc->getOldYPosPx() + OFFSETYSIZE, SIZE, SIZE, BLACK);
		} else if(mp->getFieldValue(pl_nc->getOldXPos(), (pl_nc->getOldYPos() + 1)) >= 5){
			lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETX, pl_nc->getOldYPosPx() + OFFSETYSIZE, SIZE, SIZE, RED2);
		}
	}

	if(mp->getFieldValue(pl_nc->getOldXPos(), pl_nc->getOldYPos()) == 0){
		lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETX, pl_nc->getOldYPosPx() + OFFSETY, SIZE, SIZE, BLACK);
	} else if(mp->getFieldValue(pl_nc->getOldXPos(), pl_nc->getOldYPos()) >= 5){
		lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETX, pl_nc->getOldYPosPx() + OFFSETY, SIZE, SIZE, RED2);
	}

	switch(pl_nc->getStatus()){
		case 0: WA->drawStanding(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
		case 1: WA->drawLeft	(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
		case 2: WA->drawRight	(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
		case 3: WA->drawUp		(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
		case 4: WA->drawDown	(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
	}
	pl_nc->updatePos();		//update player so the old position is the current position
}

void GameField::updateGameField_pl_ir(){
  
  switch(pl_ir->getStatus()){
    case 0: WA->drawStanding	(pl_ir->getXPx() + OFFSETXPLAYER, pl_ir->getYPx() + OFFSETYPLAYER, 2); break;
    case 1: WA->drawLeft		(pl_ir->getXPx() + OFFSETXPLAYER, pl_ir->getYPx() + OFFSETYPLAYER, 2); break;
    case 2: WA->drawRight		(pl_ir->getXPx() + OFFSETXPLAYER, pl_ir->getYPx() + OFFSETYPLAYER, 2); break;
    case 3: WA->drawUp			(pl_ir->getXPx() + OFFSETXPLAYER, pl_ir->getYPx() + OFFSETYPLAYER, 2); break;
    case 4: WA->drawDown		(pl_ir->getXPx() + OFFSETXPLAYER, pl_ir->getYPx() + OFFSETYPLAYER, 2); break;
  }
  pl_ir->updatePos();   //update player so the old position is the current position
}

void GameField::placeBombNC(){
	uint8_t bombX = pl_nc->getBombX();					//get location based on player location and offset do not use getter constant because off calculations
	uint8_t bombY = pl_nc->getBombY();					//get location based on player location and offset do not use getter constant because off calculations
	if(!(mp->getFieldValue(bombX, bombY) >= 5)){		//check if there is a bomb on that location
		mp->setFieldValue(bombX, bombY, 5);				//place bomb so there is no possibility to place another bomb
		uint8_t curBombIndex = bombsIndex;
		bombs[bombsIndex] = new Bomb(true, bombX, bombY, pl_nc->getBombRange());		//create new bomb for nunchuck player
		bombsIndex++;																	//update index of bomb

		pl_nc->minBomb();												//update player amount of bombs

		uint16_t bombByte = bombY;
		bombByte = bombX << 4;		
		bombByte = bombs[curBombIndex]->getTime() << 8;
		IRS->bombToBuff(bombByte);

		lcd->fillRect(bombX * SIZE + OFFSETX, bombY * SIZE + OFFSETY, SIZE, SIZE, RED2);	//draw bomb
		/************************************************************************/
		/* draw player so the player is visible after placement                 */
		/************************************************************************/
		switch(pl_nc->getStatus()){
			case 0: WA->drawStanding(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
			case 1: WA->drawLeft	(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
			case 2: WA->drawRight	(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
			case 3: WA->drawUp		(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
			case 4: WA->drawDown	(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
		}
	}
	
}

void GameField::placeBombIR(){
	uint16_t bombByte = IRR->bombFromBuff();
	uint8_t bombX = (bombByte & (15 << 4)) >> 4;
	uint8_t bombY = bombByte & (15 << 0);

	bombs[bombsIndex] = new Bomb(false, bombX, bombY, pl_ir->getBombRange());

	mp->setFieldValue(bombX, bombY, 5);

	lcd->fillRect(bombX * SIZE + OFFSETX, bombY * SIZE + OFFSETY, SIZE, SIZE, RED2);	//draw bomb
	/************************************************************************/
	/* draw player so the player is visible after placement                 */
	/************************************************************************/
	switch(pl_nc->getStatus()){
		case 0: WA->drawStanding(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
		case 1: WA->drawLeft	(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
		case 2: WA->drawRight	(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
		case 3: WA->drawUp		(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
		case 4: WA->drawDown	(pl_nc->getXPx() + OFFSETXPLAYER, pl_nc->getYPx() + OFFSETYPLAYER, 1); break;
	}
}

void GameField::updateBombs(){
	for(int i = 0; i < bombsIndex; i++){			//loop through every existing bomb of both players
		if(bombs[i]->updateBomb()){					//update bomb if timer is up the bomb has to explode
			explodeBomb(i);							//call explode bomb
			updateBombArray(i);						//update bomb array
			i--;									//update i so you pass no bombs
		}
	}
}

void GameField::updateBombArray(uint8_t index){
	if(bombs[index]->updatePlayer()){				//check if bomb is owned by the nunchuck player
		pl_nc->plusBomb();							//give nunchuck player his bomb back
	}
	delete bombs[index];							//completely deletes bomb
	int ind;										//is index needed to loop through the last bombs
	for(ind = index; ind < bombsIndex; ind++){		//loops through the array of pointers to bombs from current index to last index
		bombs[ind] = bombs[ind + 1];				//
	}
	bombs[ind] = NULL;
	bombsIndex--;
}

void GameField::explodeBomb(uint8_t index){
	//Serial.println("explodeBomb");
	mp->setFieldValue(bombs[index]->getX(), bombs[index]->getY(), 0);
	lcd->fillRect(bombs[index]->getX() * SIZE + OFFSETX, bombs[index]->getY() * SIZE + OFFSETY, SIZE, SIZE, BLACK);
	pl_nc->checkExplosion(bombs[index]->getX(), bombs[index]->getY());

	for(uint8_t dir = 1; dir < 5; dir++){					//loops through each direction to destroy all BACKGROUNDs in that direction
		for(uint8_t explodeoffset = 1; explodeoffset <= bombs[index]->getRange(); explodeoffset++){			//checks every BACKGROUND from offset 1 to explode range for every direction in above for
			uint8_t explosionX;
			uint8_t explosionY;
			switch(dir){															//this switch case sets for each direction the correct X and Y
				case 1:																//LEFT
				explosionX = bombs[index]->getX() - explodeoffset;
				explosionY = bombs[index]->getY();
				break;

				case 2:																//RIGHT
				explosionX = bombs[index]->getX() + explodeoffset;
				explosionY = bombs[index]->getY();
				break;

				case 3:																//UP
				explosionX = bombs[index]->getX();
				explosionY = bombs[index]->getY() - explodeoffset;
				break;
				
				case 4:																//DOWN
				explosionX = bombs[index]->getX();
				explosionY = bombs[index]->getY() + explodeoffset;
				break;
			}
			if(explosionX > 10){					//if explosionX is bigger than 10 the x coordinate is outside of the game
				break;
				} else if (explosionY > 8){				//if explosionY is bigger than 8 the y coordinate is outside of the gamed
				break;
			}


			uint8_t fieldValue = mp->getFieldValue(explosionX, explosionY);
			if (fieldValue == 1)
			{
				// 				Serial.println("wall-break");
				break;
				} else if(fieldValue == 2) {
				mp->setFieldValue(explosionX, explosionY, 0);
				lcd->fillRect(explosionX * SIZE + OFFSETX, explosionY * SIZE + OFFSETY, SIZE, SIZE, BLACK);
				// 				Serial.println("BACKGROUND destroyed break");
				break;
				} else if(fieldValue >= 5) {
				//TODO explode next bom
				// 				Serial.println("another Bomb");
			}

			pl_nc->checkExplosion(explosionX, explosionY);
		}
	}
}