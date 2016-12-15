// RRR (Alles met RRR heeft Rutger aangepast)
#include "Bomb.h"

Bomb::Bomb()
{
	bool explosion = false;
}

Bomb::putBomb()
{
	if ((MP->getFieldValue(xPos, yPos) == 0))
	{
		(MP->setFieldValue(xPos, yPos, 5))	// Empty space becomes a bomb.
	}
}

Bomb::~Bomb()
{
}

void Bomb::explode()
{

}
