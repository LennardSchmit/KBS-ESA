#ifndef _PLAYER_NC_h
#define _PLAYER_NC_h
#include "Player.h"
#include "NunchukLibrary.h"
#include "Map.h"

class Player_NC: public Player{
	public:
	Player_NC(Map* MP_g, NunchukLibrary* NC_g): Player(MP_g),NC(NC_g){}
  ~Player_NC();
	bool updatePlayer();

  private:
    NunchukLibrary* NC;
  };

#endif

