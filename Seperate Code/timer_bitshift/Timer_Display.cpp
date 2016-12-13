#include "Arduino.h"
#include "Timer_Display.h"

Timer_Display::Timer_Display(){
	time[0] = 9;				//contains the left value (tens)
	time[1] = 9;				//contains the right value
	DDRC |= (1 << PORTC1);		//data  pin
	DDRC |= (1 << PORTC2);		//clock pin
	DDRC |= (1 << PORTC3);		//latch pin
}

bool Timer_Display::nextsecond(){
	if(!(time[1])){				//check if small value is 0
		if(!(time[0])){			//check if big value = 0
			time[0] = 10;		//set up display for showing 2 stripes
			time[1] = 10;
			shiftOut();
			return true;			//return that time is up
		} else {
			time[0]--;			//make the left value one smaller
		}
		time[1] = 9;				//set right value to 9 for next cycle
	} else {
		time[1]--;				//make right value one smaller
	}
	shiftOut();
	return false;
}
/************************************************************************/
/* this function is based on Arduino shift out it uses bit banging      */
/************************************************************************/
void Timer_Display::shiftOut()
{
	PORTC &= ~(1 << PORTC3);							//disable bit shift register output
	uint8_t i, n;
	for(n = 0; n < 2; n++){
		for (i = 7; i < 255; i--)  {
			if(!!(digit_code[time[n]] & (1 << i)))	//this if and else sets the value of bit i to 0 or 1
				PORTC |=  (1 << PORTC1);
			else
				PORTC &= ~(1 << PORTC1);
			PORTC |=  (1 << PORTC2);					//sets clock on and off to send bit
			PORTC &= ~(1 << PORTC2);
		}
	}
	PORTC |=  (1 << PORTC3);							//enable bit shift register output
}
