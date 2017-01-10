#include "MI0283QT9.h"
#include "EEPROM.h"
#include "Color.h"
#include "WatchHighScore.h"
#include "Arduino.h"

WatchHighScore::WatchHighScore(MI0283QT9* lcd_g){
	lcd = lcd_g;
	unsigned char Scores[10][5];
  for(uint8_t i; i<10; i++){
    Scores[i][0]=Scores[i][1]=Scores[i][2] = 45;
    Scores[i][3]=Scores[i][4]=0;
  }
  /*
  for(int i = 0; i < ((EEPROM.size/5)-30); i++){
    boolean done = false;
    int j = i*5 - 30;
    uint8_t byte1 = EEPROM.read(j+3);
    uint8_t byte2 = EEPROM.read(j+4);
    if(EEPROM.read(j)!=255){
      for(uint8_t p = 0; p < 10; p++){
        if(!done){
          if((((Scores[p][3] << 8) & 0xFFFF) + ((Scores[p][4]) & 0xFF)) < (((byte1 << 8) & 0xFFFF) + ((byte2) & 0xFF))){
            Scores[p
          }
        }
      }
    }
  }
  */
  //Lees de waarden uit EEPROM en gooi ze in een array
  for(uint8_t i = 0; i < 10; i++){
    if(EEPROM.read((i*5)+30)!=255){
      Scores[i][0] = EEPROM.read((i*5)+30);
      Scores[i][1] = EEPROM.read((i*5)+30 + 1);
      Scores[i][2] = EEPROM.read((i*5)+30 + 2);
      Scores[i][3] = EEPROM.read((i*5)+30 + 3);
      Scores[i][4] = EEPROM.read((i*5)+30 + 4);
    }
  }
  //Sorteer de array op grootte van de score
  char iTempOne = 0;
  char iTempTwo = 0;
  for (int i = 0; i < 10; i++)
  {
    unsigned int one = ((Scores[i][3] << 8) & 0xFFFF) + ((Scores[i][4]) & 0xFF);
    for (int j = i + 1; j <= 10; j++)
    {   
          
      unsigned int two = ((Scores[j][3] << 8) & 0xFFFF) + ((Scores[j][4]) & 0xFF);
      if (one < two)
      {
        iTempOne = Scores[i][3];
        iTempTwo = Scores[i][4];
        Scores[i][3] = Scores[j][3];
        Scores[i][4] = Scores[j][4];
        Scores[j][3] = iTempOne;
        Scores[j][4] = iTempTwo;
      }
    }
  }
  //Print vervolgens de scores
  lcd->fillScreen(BACKGROUND);
 
  lcd->fillRect(5, 5, 310, 165, BLACK);
  lcd->fillRoundRect(35, 190, 250, 40, 10, BLACK);
  lcd->drawText(65, 205, "Back To Menu", RED, BLACK, 2);

  lcd->drawText(45, 10, "HIGHSCORES", RED, BLACK, 3);
  lcd->drawText(10, 50, "1", RED, BLACK, 2);
  lcd->drawText(10, 75, "2", RED, BLACK, 2);
  lcd->drawText(10, 100, "3", RED, BLACK, 2);
  lcd->drawText(10, 125, "4", RED, BLACK, 2);
  lcd->drawText(10, 150, "5", RED, BLACK, 2);
  
  lcd->drawText(165, 50, "6", RED, BLACK, 2);
  lcd->drawText(165, 75, "7", RED, BLACK, 2);
  lcd->drawText(165, 100, "8", RED, BLACK, 2);
  lcd->drawText(165, 125, "9", RED, BLACK, 2);
  lcd->drawText(157, 150, "10", RED, BLACK, 2);
  
  for(uint8_t i = 0; i < 5; i++){
    if(Scores[i][0]!=255){
      unsigned int p = ((Scores[i][3] << 8) & 0xFFFF) + ((Scores[i][4]) & 0xFF);
      lcd->drawChar(35, (50 + (i*25)), Scores[i][0], RED, BLACK, 2);
      lcd->drawChar(50, (50 + (i*25)), Scores[i][1], RED, BLACK, 2);
      lcd->drawChar(65, (50 + (i*25)), Scores[i][2], RED, BLACK, 2);
      lcd->drawInteger(90, (50 + (i*25)), p, 10,  RED, BLACK, 2);
    }
  }

  for(uint8_t i = 5; i < 10; i++){
    if(Scores[i][0]!=255){
      unsigned int p = ((Scores[i][3] << 8) & 0xFFFF) + ((Scores[i][4]) & 0xFF);
      lcd->drawChar(190, (50 + ((i-5)*25)), Scores[i][0], RED, BLACK, 2);
      lcd->drawChar(205, (50 + ((i-5)*25)), Scores[i][1], RED, BLACK, 2);
      lcd->drawChar(220, (50 + ((i-5)*25)), Scores[i][2], RED, BLACK, 2);
      lcd->drawInteger(245, (50 + ((i-5)*25)), p, 10,  RED, BLACK, 2);
    }
  } 
}

void WatchHighScore::Update(){
  lcd->touchRead();
  if(lcd->touchZ()){
    if(lcd->touchX()>35 && lcd->touchX()<285 && lcd->touchY()>190 && lcd->touchY()<230)
    {
      lcd->fillRoundRect(35, 190, 250, 40, 10, RED);
      lcd->drawText(65, 205, "Back To Menu", BLACK, RED, 2);
      status = 0;
    }
  }
}

uint8_t WatchHighScore::getStatus(){
  return status;
}

