#include "Menu.h"

#define BACKGROUND    RGB( 116, 130, 143)      //this is the color for the blocks on the outside as well as the blocks that are undestroyable in the game
#define BLACK   RGB(52, 54, 65)       //this is the color for the field you are standing on
#define RED   RGB(194, 91, 86)    //this is the color for the block that are destroyable
       
//MI0283QT9 lcd;
Menu::Menu(MI0283QT9* lcd_g)
{
	lcd = lcd_g;
  lcd->touchRead();
	lcd->fillScreen(BACKGROUND);
  lcd->fillRoundRect(60, 40, 200, 50, 10, BLACK);
  lcd->drawText(80, 60, "Start Game", RED, BLACK, 2);
  lcd->fillRoundRect(60, 150, 200, 50, 10, BLACK);
  lcd->drawText(105, 170, "Options", RED, BLACK, 2);
}

void Menu::Update()
{
  lcd->touchRead();
  if(lcd->touchZ()){
    if(lcd->touchX()>60 && lcd->touchX()<270 && lcd->touchY()>45 && lcd->touchY()<95)
    {
      lcd->fillRoundRect(60, 40, 200, 50, 10, RED);
      lcd->drawText(80, 60, "Start Game", BLACK, RED, 2);
      lcd->fillRoundRect(60, 150, 200, 50, 10, BLACK);
      lcd->drawText(105, 170, "Options", RED, BLACK, 2);
      status = 1;
    } 
    else if(lcd->touchX()>60 && lcd->touchX()<270 && lcd->touchY()>155 && lcd->touchY()<205)
    {
      lcd->fillRoundRect(60, 40, 200, 50, 10, BLACK);
      lcd->drawText(80, 60, "Start Game", RED, BLACK, 2);
      lcd->fillRoundRect(60, 150, 200, 50, 10, RED);
      lcd->drawText(105, 170, "Options", BLACK,RED, 2);
      status = 2;      
    }
  }
  
}
 
uint8_t Menu::getStatus()
{
	return status;
}
