// irRecv.h

#ifndef _IRRECV_h
#define _IRRECV_h

#include <avr/io.h>
#include <avr/interrupt.h>


class irRecv
{
	public:
		irRecv();
		int getCount();
		void setCount(int);
	private:
		int count;
};

#endif

