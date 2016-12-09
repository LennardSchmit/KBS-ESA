
/*
 * Sketch2.cpp
 *
 * Created: 12/7/2016 9:31:46 AM
 * Author : D.Hergaarden
 */ 

#include <avr/io.h>
#include "irRecv.h"
#include "irSend.h"

irSend *IRs = new irSend();
irRecv *IRr = new irRecv();

int a; //Tijd tussen de pulsen
int rc = 0; //het aantal onvangen bits (enen en nullen)
int start = 0; //Wanneer het startsignaal is ontvangen hoogt deze op
int stop = 0; //wanneer 8 bits zijn ontvangen moet deze op hogen. Weet niet zeker of dit goed gaat.
int rcByte = 0; //De ontvangen byte
int lastByte = 0; // Hier wordt rcbyte ingezet na het ontvangen
int test; // test variable voor het printen in de serial

ISR(TIMER2_COMPB_vect)
{
	IRr->setCount((IRr->getCount() + 1)); //Verhoog de count variabele in de klasse irRecv. Hier wordt a mee berekend.
}

ISR (INT0_vect)
{
	PORTB ^= (1 << PORTB0); //Schakel poort 8 aan en uit bij het ontvangen van een puls
	if(rc == 7) // Als de byte is ontvangen.
	{	
		start=0; // Zet start op 0 zodat er geen aanpassing meer worden gedan aan rcbyte
		if(stop > 0) //Wanneer de stop bit afgelopen is is stop 1 en wordt alles op 0 gezet en rcbyte in lastbyte
		{	
			//test = rcByte;
			rc = 0;
			start = 0;
			stop = 0;
			lastByte = rcByte;
			
		}
		else stop++;
	}
	
	if(PIND & (1 << PIND2))
	{
		IRr->setCount(0); //Wanner het signaal op pin 2 hoog is wordt de counter op 0 gezet.
	}
	else
	{
		a = IRr->getCount(); //Zet de waarde in a wanneer het signaal laag is.
		//test = a;
		//Als het signaal laag is en de start variabele is opgehoogd en het stop signaal is nog 0
		if((start > 0) && (rc < 7) && (stop == 0))
		{
			//if(rc != 0) 
			//test = rc;

			/*
			Hier de verschillende waardes bij het aantal nullen en 1 bit. Hier zijn de if statements op gebasseerd. 
			Je kunt dit controleren door a in test te zetten.

			8 nul = 188 / 187 / 189			175 - 185

			7 nul = 166 / 167 / 165 / 		160 - 170

			6 nul = 143 / 142 / 144 		140 - 150

			5 nul = 120 / 121 / 122 		115 - 125

			4 nul = 99 / 100 / 101 / 98		95 - 105

			3 nul = 77 / 76 / 75 / 78		75 - 85

			2 nul = 54 / 54 / 53 / 56 / 57 / 55	50 - 60

			1 nul = 34 / 32 / 33 / 31		27 - 37

			1 een = 8 / 9 / 10 / 11 / 12		5 - 15

			start = +-20

			1000100011
			1000100011

			

			128 64 32 16 8 4 2 1   2346
			1  1  1          1
			*/

			if((a > 5) && (a < 15)) //1 bit
			{
				rcByte |= (1 << rc);
				rc++;
			}
			else rcByte |= (1 << rc);
						
			if((a > 27) && (a < 37)) //1 nul
			{
				rc++;
			}

			if((a > 50) && (a < 60)) //2 nul
			{
				rc+=2;
			}

			if((a > 70) && (a < 80)) //3 nul
			{
				rc+=3;
			}

			if((a > 95) && (a < 105)) //4 nul
			{
				rc+=4;
			}

			if((a > 115) && (a < 125)) //5 nul
			{
				rc+=5;
			}

			if((a > 140) && (a < 150)) //6 nul
			{
				rc+=6;
			}

			if((a > 160) && (a < 170)) //7 nul
			{
				rc+=7;
			}
		}

		if((a > 15) && (a < 25)) //start
		{
			start++;
		}
	}
}

int main(void)
{
	DDRB |= (1 << PORTB0); //poort 8 als output
	//IRs->sendByte(128); //Comment dit als je gaat ontvangen
	Serial.begin(9600);   //Comment dit als je gaat verzenden
	_delay_ms(100);
	while (1) 
    {
		Serial.println(test); //Comment dit als je gaat verzenden
		//IRs->sendByte(93); //Comment dit als he gaat ontvangen
		_delay_ms(5);
    }
}
