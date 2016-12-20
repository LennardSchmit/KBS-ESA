#ifndef Map_h
#define Map_h

#include "stdint.h"
#include "MI0283QT9.h"
// Map is implemented because two classes cannot implement each other 
class Map{
  public:
    Map(uint8_t level_g[9][11]);
    uint8_t getFieldValue(uint8_t x, uint8_t y);					//gets the value on the x, y position
    void setFieldValue(uint8_t x, uint8_t y, uint8_t value);		//sets the value of the x, y position
    //void drawField(uint8_t x, uint8_t y);
  private:
    uint8_t field[9][11];
};
#endif
