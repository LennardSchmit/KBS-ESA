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

int irRecv::fromBuff()
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

void irRecv::setStart(int setS)
{
	start = setS;
}

void irRecv::setStop(int setS)
{
	stop = setS;
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

uint8_t irRecv::getStart()
{
	return start;
}

uint8_t irRecv::getStop()
{
	return stop;
}

int irRecv::getRcByte()
{
	return rcByte;
}

uint8_t irRecv::getParity()
{
	return parity;
}

void irRecv::setParity(int par_g)
{
	parity = par_g;
}

void irRecv::bombToBuff(int inByte)
{
	bombBuffer[bombToIndex] = inByte;
	bombToIndex++;
	if(bombToIndex == BUFFER_LENGTH) bombToIndex--;
}

int irRecv::bombFromBuff()
{
	uint8_t bombIndex = bombFromIndex;
	if(bombFromIndex < bombToIndex) bombFromIndex++;
	else
	{
		bombFromIndex = 0;
		bombToIndex = 0;
		bombIndex = 0;
	}
	return bombBuffer[bombIndex];
}

bool irRecv::bombBuffAvail()
{
	return bombToIndex;
}

void irRecv::remainingToBuff(int inByte)
{
	remainingBuffer[remainingToIndex] = inByte;
	remainingToIndex++;
	if(remainingToIndex == BUFFER_LENGTH) remainingToIndex--;
}

int irRecv::remainingFromBuff()
{
	uint8_t remainingIndex = remainingFromIndex;
	if(remainingFromIndex < remainingToIndex) remainingFromIndex++;
	else
	{
		remainingFromIndex = 0;
		remainingToIndex = 0;
		remainingIndex = 0;
	}
	return remainingBuffer[remainingIndex];
}

bool irRecv::remainingBuffAvail()
{
	return remainingToIndex;
}

void irRecv::setSBuf(int selbuf)
{
	sBuf = selbuf;
}

int irRecv::getSBuf()
{
	return sBuf;
}