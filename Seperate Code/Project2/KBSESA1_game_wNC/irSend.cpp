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
	for(int i = 0; i<8; i++)
	{
		_delay_us(400);			
		if(bytes & (1 << i))
		{
			DDRD |= (1 << PORTD3);
			_delay_us(600);			
		}
		else
		{
			DDRD |= (1 << PORTD3);
			_delay_us(250);
		}
			
		DDRD &= ~(1 << PORTD3);
	}

	//Stop bit
	// Start bits
	_delay_us(400);
	DDRD |= (1 << PORTD3);
	_delay_us(900);
	DDRD &= ~(1 << PORTD3);
	_delay_us(400);
}