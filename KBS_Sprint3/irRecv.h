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
		int fromBuff();
		bool buffAvail();
		void setBitTime(int);
		void setRc(int);
		void setStart(int);
		void setStop(int);
		void setRcByte(int);
		uint8_t getBitTime();
		uint8_t getRc();
		uint8_t getStart();
		uint8_t getStop();
		int getRcByte();
		void resetRcByte();
		uint8_t getParity();
		void setParity(int);
	private:
		uint8_t count;
		uint8_t toIndex = 0;
		uint8_t fromIndex = 0;
		int *buffer[BUFFER_LENGTH]; 
		uint8_t bitTime; //Tijd tussen de pulsen
		uint8_t rc = 0; //het aantal onvangen bits (enen en nullen)
		uint8_t start = 0;
		uint8_t stop = 0;
		int rcByte = 0; //De ontvangen byte
		uint8_t parity;
};

#endif

