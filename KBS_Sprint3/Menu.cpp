#include "Menu.h"
#include "Color.h"
      
Menu::Menu(MI0283QT9* lcd_g)
{
	lcd = lcd_g;
	
	lcd->fillScreen(BACKGROUND);
  lcd->drawText(50, 20, "BOMBERMAN", RED, BACKGROUND, 3);
  lcd->fillRoundRect(60, 90, 200, 40, 10, BLACK);
  lcd->drawText(80, 105, "Start Game", RED, BLACK, 2);
  lcd->fillRoundRect(60, 140, 200, 40, 10, BLACK);
  lcd->drawText(80, 155, "Highscores", RED, BLACK, 2);
  lcd->fillRoundRect(60, 190, 200, 40, 10, BLACK);
  lcd->drawText(80, 205, "Options", RED, BLACK, 2);
}

void Menu::Update()
{
  lcd->touchRead();
  if(lcd->touchZ()){
    if(lcd->touchX()>60 && lcd->touchX()<260){
      if(lcd->touchY()>90 && lcd->touchY()<130)
      {
        lcd->fillRoundRect(60, 90, 200, 40, 10, RED);
        lcd->drawText(80, 105, "Start Game", BLACK, RED, 2);
        lcd->fillRoundRect(60, 140, 200, 40, 10, BLACK);
        lcd->drawText(80, 155, "Highscores", RED, BLACK, 2);
        lcd->fillRoundRect(60, 190, 200, 40, 10, BLACK);
        lcd->drawText(80, 205, "Options", RED, BLACK, 2);
        status = 1;
      } 
      else if(lcd->touchY()>140 && lcd->touchY()<180)
      {
        lcd->fillRoundRect(60, 90, 200, 40, 10, BLACK);
        lcd->drawText(80, 105, "Start Game", RED, BLACK, 2);
        lcd->fillRoundRect(60, 140, 200, 40, 10, RED);
        lcd->drawText(80, 155, "Highscores", BLACK, RED, 2);
        lcd->fillRoundRect(60, 190, 200, 40, 10, BLACK);
        lcd->drawText(80, 205, "Options", RED, BLACK, 2);
        status = 5;      
      }
      else if(lcd->touchY()>190 && lcd->touchY()<230)
      {
        lcd->fillRoundRect(60, 90, 200, 40, 10, BLACK);
        lcd->drawText(80, 105, "Start Game", RED, BLACK, 2);
        lcd->fillRoundRect(60, 140, 200, 40, 10, BLACK);
        lcd->drawText(80, 155, "Highscores", RED, BLACK, 2);
        lcd->fillRoundRect(60, 190, 200, 40, 10, RED);
        lcd->drawText(80, 205, "Options", BLACK, RED, 2);
        status = 2;      
      }
    }
  }
}
 
uint8_t Menu::getStatus()
{
	return status;
}
