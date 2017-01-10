#ifndef _PLAYER_NC_h
#define _PLAYER_NC_h
#include "Player.h"
#include "NunchukLibrary.h"
#include "Map.h"
#include "irSend.h"

class Player_NC: public Player{
	public:
	Player_NC(Map* MP_g, uint8_t bombs_g, NunchukLibrary* NC_g, irSend* IRS_g): Player(MP_g, bombs_g),NC(NC_g),IRS(IRS_g){}
	~Player_NC();

	bool updatePlayer();

  private:
    NunchukLibrary* NC;
	irSend* IRS;
  };

#endif

