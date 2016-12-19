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


void irSend::sendByte(int bytes_g)
{
	bytes = bytes_g;
	// Start bits
	DDRD |= (1 << PORTD3);
	_delay_us(900);
	DDRD &= ~(1 << PORTD3);

	//De byte
	for(int i = 0; i<12; i++)
	{
		_delay_us(350);			
		if(bytes & (1 << i))
		{
			DDRD |= (1 << PORTD3);
			_delay_us(600);			
		}
		else
		{
			DDRD |= (1 << PORTD3);
			_delay_us(350);
		}			
		DDRD &= ~(1 << PORTD3);
	}

	//Stop bit
	_delay_us(350);
	DDRD |= (1 << PORTD3);
	_delay_us(1200);
	DDRD &= ~(1 << PORTD3);
	_delay_us(350);
}

uint8_t irSend::getCount()
{
	return count;
}

void irSend::setCount(int newCount)
{
	count = newCount;
}

void irSend::toBuff(int inByte)
{
	buffer[toIndex] = inByte;
	toIndex++;
	if(toIndex == BUFFER_LENGTH) toIndex--;
}

int irSend::fromBuff()
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

bool irSend::buffAvail()
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