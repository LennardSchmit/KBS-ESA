// Timer_Display.h

#ifndef _TIMER_DISPLAY_h
#define _TIMER_DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Timer_Display{
	public:
	Timer_Display();
	bool nextSecond();
	void shiftOut();

	private:
	void displayDigits();
	uint8_t time[2];		
	uint8_t digit_code[11] = {126, 12, 182, 158, 204, 218, 250, 14, 254, 222, 128}; //contains the 7 segment byte value
};
#endif

