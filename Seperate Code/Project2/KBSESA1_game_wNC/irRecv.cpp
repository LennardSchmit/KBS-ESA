#include "irRecv.h"
#include <stdint.h>
irRecv::irRecv()
{
	DDRD &= ~(1 << PORTD2);
	EICRA |= (1 << ISC00);
	EIMSK |= (1 << INT0);
	sei();
	//Enable external interrupt op pin 2 bij elke logische change
}

uint8_t irRecv::getCount()
{
	return count;
}

void irRecv::setCount(int newCount)
{
	count = newCount;
}

void irRecv::toBuff(int inByte)
{
	buffer[toIndex] = inByte;
	toIndex++;
	if(toIndex == BUFFER_LENGTH) toIndex--;
}

uint8_t irRecv::fromBuff()
{
	uint8_t index = fromIndex;
	if(fromIndex < toIndex) fromIndex++;
	else 
	{
		fromIndex = 0;
		toIndex = 0;
		index = 0;
	}
	return buffer[index];
}

bool irRecv::buffAvail()
{
	return toIndex;
}

void irRecv::setBitTime(int setTime)
{
	bitTime = setTime;
}

void irRecv::setRc(int setRc)
{
	rc = setRc;
}

void irRecv::setStartStop(int setSS)
{
	startStop = setSS;
}

void irRecv::setRcByte(int bits)
{
	rcByte |= bits;
}

void irRecv::resetRcByte()
{
	rcByte = 0;
}

uint8_t irRecv::getBitTime()
{
	return bitTime;
}

uint8_t irRecv::getRc()
{
	return rc;
}

uint8_t irRecv::getStartStop()
{
	return startStop;
}

uint8_t irRecv::getRcByte()
{
	return rcByte;
}