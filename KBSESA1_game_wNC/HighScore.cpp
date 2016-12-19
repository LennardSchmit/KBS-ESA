#include "HighScore.h"
#include "MI0283QT9.h"
#include "EEPROM.h"
#include "Color.h"

HighScore::HighScore(MI0283QT9* lcd_g, int highscore_g){
	lcd = lcd_g;
	highscore = highscore_g;
	
	//lcd->fillScreen()
}
