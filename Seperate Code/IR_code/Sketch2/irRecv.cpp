// 
// 
// 

#include "irRecv.h"
irRecv::irRecv()
{
	DDRD &= ~(1 << PORTD2);
	EICRA |= (1 << ISC00);
	EIMSK |= (1 << INT0);
	sei();
	//Enable external interrupt op pin 2 bij elke logische change
}

int irRecv::getCount()
{
	return count;
}

void irRecv::setCount(int newCount)
{
	count = newCount;
}