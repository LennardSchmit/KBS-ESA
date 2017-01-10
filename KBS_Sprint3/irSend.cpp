#include "irSend.h"

irSend::irSend()
{
	
	TCCR2A =  (1 << COM2B1) | (1 << WGM21) | (1 << WGM20); 
	TCCR2B = (1 << WGM22) | (1 << CS21); //Fast PWM & prescaler /8 - 16000000/8/52 / 38,4 KHz
	OCR2A = 51; 
	OCR2B = 26;  // Duty Cycle 50%
	TIMSK2 = _BV(OCIE2B);
	//38 Khz signaal en timer
}

uint8_t irSend::getCount()
{
	return count;
}

void irSend::setCount(int newCount)
{
	count = newCount;
}

//Hieronder staat de buffer voor de player informatie. Elke andere buffer in het verzenden en ontvangen werkt op dezelfde manier.
void irSend::toBuff(int inByte) //functie om iets in de buffer te zetten. 
{
	buffer[toIndex] = inByte; //Hetgene dat in de buffer komt wordt op de plaats van de huidige index gezet.
	toIndex++; //De index wordt elke keer opgehoogt. 
	if(toIndex == BUFFER_LENGTH) toIndex--; //Als de buffer zijn maximale lengte bereikt heeft wordt de index niet meer opgehoogd.
}

int irSend::fromBuff() //Functie om gegevens uit de buffer te halen
{
	uint8_t index = fromIndex; //De fromindex houdt bij waar de buffer is met lezen.
	if(fromIndex < toIndex) fromIndex++; //Zolang de fromindex niet hoger is als de toindex. Dus niet verder gaat dan dat in de buffer staat
	else //Wannneer dat wel zo is, wordt de buffer gereset.
	{
		fromIndex = 0;
		toIndex = 0;
		index = 0;
	}
	return buffer[index]; //De return komt op het laatst omdat anders de functie afgelopen is. Daarom wordt de variabele index gebruikt.
}

bool irSend::buffAvail() //Geeft aan of de buffer gelezen kan worden. 
{
	return toIndex;
}

int irSend::getCurByte()
{
	return curByte;
}

void irSend::setCurByte(int curByte_g)
{
	curByte = curByte_g;
}

int irSend::getBitCount()
{
	return bitCount;
}

void irSend::setBitCount(int bitCount_g)
{
	bitCount = bitCount_g;
}

uint8_t irSend::getBitSend()
{
	return bitSend;
}

void irSend::setBitSend(int bitSend_g)
{
	bitSend = bitSend_g;
}

uint8_t irSend::getStart()
{
	return start;
}

void irSend::setStart(int start_g)
{
	start = start_g;
}

uint8_t irSend::getParity()
{
	return parity;
}

void irSend::setParity(int par_g)
{
	parity = par_g;
}

void irSend::bombToBuff(int inByte)
{
	bombBuffer[bombToIndex] = inByte;
	bombToIndex++;
	if(bombToIndex == BUFFER_LENGTH) bombToIndex--;
}

int irSend::bombFromBuff()
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

bool irSend::bombBuffAvail()
{
	return bombToIndex;
}

void irSend::remainingToBuff(int inByte)
{
	remainingBuffer[remainingToIndex] = inByte;
	remainingToIndex++;
	if(remainingToIndex == BUFFER_LENGTH) remainingToIndex--;
}

int irSend::remainingFromBuff()
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

bool irSend::remainingBuffAvail()
{
	return remainingToIndex;
}

void irSend::setSBuf(int selbuf)
{
	sBuf = selbuf;
}

int irSend::getSBuf()
{
	return sBuf;
}