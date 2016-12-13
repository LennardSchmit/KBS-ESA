// irSend.h

#ifndef _IRSEND_h
#define _IRSEND_h
#include <avr/io.h>
#include <util/delay.h>

class irSend
{
	public:
		irSend();
		void sendByte(int);
	private:
		int bytes;
};

#endif

