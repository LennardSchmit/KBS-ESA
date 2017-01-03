// Timer_Display.h

#ifndef _TIMER_DISPLAY_h
#define _TIMER_DISPLAY_h

class Timer_Display{
	public:
	Timer_Display();
	bool nextSecond();
	void shiftOut();

	private:
	void displayDigits();
	uint8_t time[2];		
	
	uint8_t digit_code[11] = //contains the 7 segment byte value
	{
		0b01101111,
		0b00101000,
		0b11100110,
		0b11101100,
		0b10101001,
		0b11001101,
		0b11001111,
		0b01101000,
		0b11101111,
		0b11101101,
		0b10000000
	};
	
	/*
		uint8_t digit_code[11] = //contains the 7 segment byte value
		{
			0b11110110,
			0b00010100,
			0b01100111,
			0b00110111,
			0b10010101,
			0b10110011,
			0b11110011,
			0b00010110,
			0b11110111,
			0b10110111,
			0b00000001
		};
		*/
};
#endif

