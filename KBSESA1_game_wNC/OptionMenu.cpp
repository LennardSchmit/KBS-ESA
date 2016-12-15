#include "OptionMenu.h"

#define BACKGROUND    RGB(116, 130, 143)      //this is the color for the blocks on the outside as well as the blocks that are undestroyable in the game
#define BLACK   RGB(52, 54, 65)       //this is the color for the field you are standing on
#define RED   RGB(194, 91, 86)    //this is the color for the block that are destroyable

OptionMenu::OptionMenu(MI0283QT9 *lcd_g)
{
	lcd = lcd_g;
	lcd->fillScreen(BACKGROUND);
  lcd->drawText(250, 3, "BACK", BLACK, BACKGROUND, 2);

	for(uint8_t i = 0; i<4; i++)
	{
		drawBar((i), 0);
		drawSlider((i), option[(i)], 1);
	}
}


void OptionMenu::Update()
{
  lcd->touchRead();
  if(lcd->touchZ())
  {
    if(lcd->touchX() >= 40 && lcd->touchX() <= 265)
    {
      if(lcd->touchY() >=30 && lcd->touchY() <= 70)
      {
        menuNr = 0;
        if(menuNr != menuLast)
        {
          lcd->drawText(40, (20+menuLast*50), optionName[menuLast], BLACK, BACKGROUND, 2);
          lcd->drawText(40, (20+menuNr*50), optionName[menuNr], RED, BACKGROUND, 2);
          menuLast = menuNr;
        }
        sliderUpdate(menuNr);
      }
      else if(lcd->touchY() >=83 && lcd->touchY() <= 123)
      {
        menuNr = 1;
        if(menuNr != menuLast)
        {
          lcd->drawText(40, (20+menuLast*50), optionName[menuLast], BLACK, BACKGROUND, 2);
          lcd->drawText(40, (20+menuNr*50), optionName[menuNr], RED, BACKGROUND, 2);
          menuLast = menuNr;
        }
        sliderUpdate(menuNr);
      } 
      else if(lcd->touchY() >=136 && lcd->touchY() <= 176)
      {
        menuNr = 2;
        if(menuNr != menuLast)
        {
          lcd->drawText(40, (20+menuLast*50), optionName[menuLast], BLACK, BACKGROUND, 2);
          lcd->drawText(40, (20+menuNr*50), optionName[menuNr], RED, BACKGROUND, 2);
          menuLast = menuNr;
        }
        sliderUpdate(menuNr);
      } 
      else if(lcd->touchY() >=190 && lcd->touchY() <= 230)
      {
        menuNr = 3;
        if(menuNr != menuLast)
        {
          lcd->drawText(40, (20+menuLast*50), optionName[menuLast], BLACK, BACKGROUND, 2);
          lcd->drawText(40, (20+menuNr*50), optionName[menuNr], RED, BACKGROUND, 2);
          menuLast = menuNr;
        }
        sliderUpdate(menuNr);
      }
    }
    if(lcd->touchX()>250 && lcd->touchY()<20){
      lcd->drawText(250, 3, "BACK", RED, BACKGROUND, 2);
      status = 0;
    }
  }
  
}

void OptionMenu::sliderUpdate(int item)
{
  oldOption = option[item];
  option[item] = map(lcd->touchX(), 40, 260, 0, 9);
  if(option[item] != oldOption)
  {
    drawSlider(item, option[item], 1);
    drawSlider(item, oldOption, 0);
    if(item == 3 && option[item] == 0){
      //SELECT RANDOM GENERATED MAP HERE
      lcd->drawText(280, (((item+1)*50)-5), "R", BLACK, BACKGROUND, 2);
    } else{
      lcd->drawInteger(280, (((item+1)*50)-5), option[item], 11, BLACK, BACKGROUND, 2);
    }
  }
}

void OptionMenu::drawSlider(int item, int slideValue, int draw)
{
	item++;
	item*=50;
	slideValue*=23;
	if(draw)
	{
		lcd->drawLine((45+slideValue), (item-10), (45+slideValue), (item+10), RED);
	}
	else
	{
		lcd->drawLine((45+slideValue), (item-10), (45+slideValue), (item+10), BACKGROUND);
		lcd->drawPixel((45+slideValue), item, BLACK);
	}
}


void OptionMenu::drawBar(int itemNr, int tab)
{
	int item = itemNr;
	item++;
	item*=50;
	lcd->drawText(40, (item-30), optionName[itemNr], BLACK, BACKGROUND, 2); // text
	lcd->drawLine(40, item, 257, item, BLACK); //x
	lcd->drawLine(40, (item-10), 40, (item+10), BLACK); //y
	lcd->drawLine(257, (item-10), 257, (item+10), BLACK); //y
	lcd->drawInteger(280, (((itemNr+1)*50)-5), option[itemNr], 11, BLACK, BACKGROUND, 2);

	for(int i=0; i<tab; i++) lcd->drawLine((50+(i*10)), (item-10), (50+(i*10)), (item+10), BLACK);
}

uint8_t OptionMenu::getStatus()
{
	return status;
}

uint8_t OptionMenu::getSelectedLevel(){
  return option[3];
}

