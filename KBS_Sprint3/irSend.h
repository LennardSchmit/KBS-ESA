// irSend.h

#ifndef _IRSEND_h
#define _IRSEND_h
#include <avr/io.h>
#include <util/delay.h>

class irSend
{

	#define BUFFER_LENGTH 32

	public:
		irSend();
		uint8_t getCount();
		void setCount(int);
		void sendByte(int);
		void toBuff(int);
		int fromBuff();
		bool buffAvail();
		int getCurByte();
		void setCurByte(int);
		int getBitCount();
		void setBitCount(int);
		uint8_t getBitSend();
		void setBitSend(int);
		uint8_t getStart();
		void setStart(int);
		uint8_t getParity();
		void setParity(int);
		void bombToBuff(int);
		int bombFromBuff();
		bool bombBuffAvail();
		void remainingToBuff(int);
		int remainingFromBuff();
		bool remainingBuffAvail();
		int getSBuf();
		void setSBuf(int);
	private:
		int bytes;
		uint8_t count;
		uint8_t bitCount;
		int curByte;
		uint8_t bitSend;
		uint8_t start;
		uint8_t toIndex = 0;
		uint8_t fromIndex = 0;
		int *buffer[BUFFER_LENGTH];
		uint8_t parity;
		uint8_t bombToIndex = 0;
		uint8_t bombFromIndex = 0;
		int *bombBuffer[BUFFER_LENGTH];
		uint8_t remainingToIndex = 0;
		uint8_t remainingFromIndex = 0;
		int *remainingBuffer[BUFFER_LENGTH];
		int sBuf;
};

#endif