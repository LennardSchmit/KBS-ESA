// irRecv.h

#ifndef _IRRECV_h
#define _IRRECV_h

#include <avr/io.h>
#include <avr/interrupt.h>


class irRecv
{
	#define BUFFER_LENGTH 32

	public:
		irRecv();
		uint8_t getCount();
		void setCount(int);
		void toBuff(int);
		uint8_t fromBuff();
		bool buffAvail();
		void setBitTime(int);
		void setRc(int);
		void setStartStop(int);
		void setRcByte(int);
		uint8_t getBitTime();
		uint8_t getRc();
		uint8_t getStartStop();
		uint8_t getRcByte();
		void resetRcByte();

	private:
		uint8_t count;
		uint8_t toIndex = 0;
		uint8_t fromIndex = 0;
		uint8_t *buffer[BUFFER_LENGTH]; 
		uint8_t bitTime; //Tijd tussen de pulsen
		uint8_t rc = 0; //het aantal onvangen bits (enen en nullen)
		uint8_t startStop = 0; //Wanneer het startsignaal is ontvangen hoogt deze op
		uint8_t rcByte = 0; //De ontvangen byte
};

#endif

