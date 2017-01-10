#include "SaveHighScore.h"
#include "MI0283QT9.h"
#include "EEPROM.h"
#include "Color.h"

SaveHighScore::SaveHighScore(MI0283QT9* lcd_g, int highscore_g){
	lcd = lcd_g;
	highscore = highscore_g;

  //De letters zijn standaard I I I omdat de I in het midden van het alfabet zit.
  letterOne = letterTwo = letterThree = 73;
  press = false;
  
  //Teken het scherm
	lcd->fillScreen(BACKGROUND);
  lcd->fillRect(34, 46, 32, 30, BLACK);
  lcd->fillRect(84, 46, 32, 30, BLACK);
  lcd->fillRect(134, 46, 32, 30, BLACK);
  lcd->drawChar(41, 50, letterOne, RED, BLACK, 3);
  lcd->drawChar(91, 50, letterTwo, RED, BLACK, 3);
  lcd->drawChar(141, 50, letterThree, RED, BLACK, 3);

  lcd->fillTriangle(34, 40, 66, 40, 50, 20, BLACK);
  lcd->fillTriangle(84, 40, 116, 40, 100, 20, BLACK);
  lcd->fillTriangle(134, 40, 166, 40, 150, 20, BLACK);

  lcd->fillTriangle(34, 82, 66, 82, 50, 102, BLACK);
  lcd->fillTriangle(84, 82, 116, 82, 100, 102, BLACK);
  lcd->fillTriangle(134, 82, 166, 82, 150, 102, BLACK);

  lcd->fillRect(195, 46, 102, 30, BLACK);
  lcd->drawInteger(200, 50, highscore, 10, RED, BLACK, 3);

  lcd->fillRoundRect(35, 190, 250, 40, 10, BLACK);
  lcd->drawText(65, 205, "Save", RED, BLACK, 2);

}

void SaveHighScore::Update(){
  lcd->touchRead();
  if(lcd->touchZ()){
    if(!press){
      if(lcd->touchX()>30 && lcd->touchX()<70)
      {
        if(lcd->touchY()> 15 && lcd->touchY()<40)
        {
          lcd->fillTriangle(34, 40, 66, 40, 50, 20, RED);
          letterOne = charPlus(letterOne);
          lcd->drawChar(41, 50, letterOne, RED, BLACK, 3);
        } 
        else if(lcd->touchY()> 76 && lcd->touchY()<102)
        {
          lcd->fillTriangle(34, 82, 66, 82, 50, 102, RED);
          letterOne = charMinus(letterOne);
          lcd->drawChar(41, 50, letterOne, RED, BLACK, 3);
        }
      } else if(lcd->touchX()>80 && lcd->touchX()<120)
      {
        if(lcd->touchY()> 15 && lcd->touchY()<40)
        {
          lcd->fillTriangle(84, 40, 116, 40, 100, 20, RED);
          letterTwo = charPlus(letterTwo);
          lcd->drawChar(91, 50, letterTwo, RED, BLACK, 3);
        } 
        else if(lcd->touchY()> 76 && lcd->touchY()<102)
        {
          lcd->fillTriangle(84, 82, 116, 82, 100, 102, RED);
          letterTwo = charMinus(letterTwo);
          lcd->drawChar(91, 50, letterTwo, RED, BLACK, 3);
        }
      } 
      else if(lcd->touchX()>130 && lcd->touchX()<170)
      {
        if(lcd->touchY()> 15 && lcd->touchY()<40)
        {
          lcd->fillTriangle(134, 40, 166, 40, 150, 20, RED);
          letterThree = charPlus(letterThree);
          lcd->drawChar(141, 50, letterThree, RED, BLACK, 3);
        } 
        else if(lcd->touchY()> 76 && lcd->touchY()<102)
        {
          lcd->fillTriangle(134, 82, 166, 82, 150, 102, RED);
          letterThree = charMinus(letterThree);
          lcd->drawChar(141, 50, letterThree, RED, BLACK, 3);
        }
      }
      press = true;
    } else{
      lcd->fillTriangle(34, 40, 66, 40, 50, 20, BLACK);
      lcd->fillTriangle(84, 40, 116, 40, 100, 20, BLACK);
      lcd->fillTriangle(134, 40, 166, 40, 150, 20, BLACK);
      
      lcd->fillTriangle(34, 82, 66, 82, 50, 102, BLACK);
      lcd->fillTriangle(84, 82, 116, 82, 100, 102, BLACK);
      lcd->fillTriangle(134, 82, 166, 82, 150, 102, BLACK);
      press = false;
    }

    if(lcd->touchX()>35 && lcd->touchX()<285 && lcd->touchY()>190 && lcd->touchY()<230){
      SaveScore();
      status = 0;
    }
  }
}

//Hier wordt de highscore opgeslagen in EEPROM
void SaveHighScore::SaveScore(){
  int addr = 30;
  uint8_t byte1 = ((highscore>>8) & 0xFF);
  uint8_t byte2 = (highscore & 0xFF);
  
  while(1){
    if(EEPROM.read(addr)==255){
        EEPROM.write(addr, letterOne);
        EEPROM.write(addr+1, letterTwo);
        EEPROM.write(addr+2, letterThree);
        EEPROM.write(addr+3, byte1);
        EEPROM.write(addr+4, byte2);
        status = 0;
        break;
    } else{
      addr+=5;
    }
  }
}

uint8_t SaveHighScore::getStatus(){
  return status;
}

unsigned char SaveHighScore::charMinus(char i){
  if(i > 65){
    i--;
  }
  return i;
}

unsigned char SaveHighScore::charPlus(char i){
  if(i < 90){
    i++;
  }
  return i;
}

