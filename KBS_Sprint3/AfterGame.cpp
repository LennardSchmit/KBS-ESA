#include "AfterGame.h"
#include "WalkingAnimation.h"
#include "Color.h"

AfterGame::AfterGame(MI0283QT9* lcd_g, WalkingAnimation* WA_g, int playerOneScore, int playerTwoScore){
		lcd = lcd_g;
    WA = WA_g;

		lcd->fillScreen(BACKGROUND);

    //Draw the players in a square
    lcd->fillRect(70, 30, 48, 64, BLACK);
    lcd->fillRect(206, 30, 48, 64, BLACK);
    WA->drawBigStanding(76, 38, 1);
    WA->drawBigStanding(212, 38, 2);
    #ifdef P1
    //Buttons on the bottom of the screen
    lcd->fillRoundRect(35, 140, 250, 40, 10, BLACK);
    lcd->drawText(55, 155, "Save Highscore", RED, BLACK, 2);
    lcd->fillRoundRect(35, 190, 250, 40, 10, BLACK);
    lcd->drawText(65, 205, "Back To Menu", RED, BLACK, 2);
    #endif
    
    //Select the winner
    if(playerOneScore>playerTwoScore){
      lcd->drawRect(68, 28, 52, 68, RED);
      lcd->drawRect(69, 29, 50, 66, RED);
      lcd->drawText(48, 10, "WINNER", RED, BACKGROUND, 2);
      lcd->drawText(191, 10, "LOSER", BLACK, BACKGROUND, 2);
      lcd->drawInteger(63, 101, playerOneScore, 10, RED, BACKGROUND, 2);
      lcd->drawInteger(201, 101, playerTwoScore, 10, BLACK, BACKGROUND, 2);
      highScore = playerOneScore;
    } else if(playerOneScore<playerTwoScore){
      lcd->drawRect(204, 28, 52, 68, RED);
      lcd->drawRect(205, 29, 50, 66, RED);
      lcd->drawText(55, 10, "LOSER", BLACK, BACKGROUND, 2);
      lcd->drawText(184, 10, "WINNER", RED, BACKGROUND, 2);
      lcd->drawInteger(63, 101, playerOneScore, 10, BLACK, BACKGROUND, 2);
      lcd->drawInteger(201, 101, playerTwoScore, 10, RED, BACKGROUND, 2);
      highScore = playerTwoScore;
    } else{
      lcd->drawRect(68, 28, 52, 68, RED);
      lcd->drawRect(69, 29, 50, 66, RED);
      lcd->drawRect(204, 28, 52, 68, RED);
      lcd->drawRect(205, 29, 50, 66, RED);
      lcd->drawText(68, 10, "TIE", RED, BACKGROUND, 2);
      lcd->drawText(204, 10, "TIE", RED, BACKGROUND, 2);
      lcd->drawInteger(63, 101, playerOneScore, 10, RED, BACKGROUND, 2);
      lcd->drawInteger(201, 101, playerTwoScore, 10, RED, BACKGROUND, 2);
      highScore = playerOneScore;
    }
}

void AfterGame::Update(){
	lcd->touchRead();
  if(lcd->touchZ()){
    if(lcd->touchX()>35 && lcd->touchX()<285 && lcd->touchY()>140 && lcd->touchY()<180)
    {
      lcd->fillRoundRect(35, 140, 250, 40, 10, RED);
      lcd->drawText(55, 155, "Save Highscore", BLACK, RED, 2);
      lcd->fillRoundRect(35, 190, 250, 40, 10, BLACK);
      lcd->drawText(65, 205, "Back To Menu", RED, BLACK, 2);
      status = 4;
    }
    else if(lcd->touchX()>35 && lcd->touchX()<285 && lcd->touchY()>190 && lcd->touchY()<230)
    {
      lcd->fillRoundRect(35, 140, 250, 40, 10, BLACK);
      lcd->drawText(55, 155, "Save Highscore", RED, BLACK, 2);
      lcd->fillRoundRect(35, 190, 250, 40, 10, RED);
      lcd->drawText(65, 205, "Back To Menu", BLACK, RED, 2);
      status = 0;
    }
  }
}

uint8_t AfterGame::getStatus()
{
  return status;
}

int AfterGame::getHighScore(){
  return highScore;
}

