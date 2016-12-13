#include "Timer_Display.h"
#include "Arduino.h"

int main(void){
	//init();
	Timer_Display* timer1 = new Timer_Display();
	bool timesup = true;
	while(timesup){
		if(timer1->nextsecond()){
			timesup = false;			
		}
	}
}