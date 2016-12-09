// Menu.h

#ifndef _MENU_h
#define _MENU_h
#include <Arduino.h>
#include <EEPROM.h>
#include <MI0283QT9.h>
#include "NunchukLibrary.h"
#define ADDRESS 0x52

class Menu {
	public:
	Menu(MI0283QT9 *lcd_g);
	void Update();
	uint8_t getStatus();
  void writeCalData(void);
  uint8_t readCalData(void);
  
	private:
	MI0283QT9 *lcd;
	uint8_t menuNr = 0;
	uint8_t menuLast = 1;
	uint8_t status = 0;
};
#endif
