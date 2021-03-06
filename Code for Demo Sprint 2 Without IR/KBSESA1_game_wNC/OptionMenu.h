// OptionMenu.h
#ifndef _OPTIONMENU_h
#define _OPTIONMENU_h

#include <Arduino.h>
#include <MI0283QT9.h>
#include "NunchukLibrary.h"

class OptionMenu 
{
	public:
  	OptionMenu(MI0283QT9 *lcd_g);
  	void Update();
  	uint8_t getStatus();
    uint8_t getSelectedLevel();
    
	private:
  	//------Game Options------//
  	String optionName[4] = {
  		"BrightNess",
  		"GameSpeed",
  		"Bomb Density",
  		"Level Select"
  	};
  	//-----Startup Default----//
  	int option[4] = {
  		9, //Brightness
  		5, //GameSpeed
  		7,  //Bomb Density
  		1   //level
  	};
  	//------------------------//

	NunchukLibrary *nc;
	MI0283QT9 *lcd;
	uint8_t menuNr = 0;
	uint8_t menuLast = 1;
	uint8_t oldBrightness;
	uint8_t oldOption;
	uint8_t status = 2;
	void drawSlider(int, int, int);
	void drawBar(int, int);
	void sliderUpdate(int item);
};
#endif
