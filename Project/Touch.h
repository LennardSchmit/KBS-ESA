#ifndef Touch_h
#define Touch_h

#include "MI0283QT9.h"
#include "EEPROM.h"

class Touch{
  public:
    Touch(MI0283QT9* lcd_g){
      lcd = lcd_g;
      if(lcd->touchZ() || readCalData()) //calibration data in EEPROM?
      {
        lcd->touchStartCal(); //calibrate touchpanel
        writeCalData(); //write data to EEPROM
      }
    }
    
    void writeCalData(void)
    {
      uint16_t i, addr=0;
      uint8_t *ptr;
    
      EEPROM.write(addr++, 0xAA);
      
      ptr = (uint8_t*)&lcd->tp_matrix;
      for(i=0; i < sizeof(CAL_MATRIX); i++)
      {
        EEPROM.write(addr++, *ptr++);
      }
    
      return;
    }
    
    uint8_t readCalData(void)
    {
      uint16_t i, addr=0;
      uint8_t *ptr;
      uint8_t c;
    
      c = EEPROM.read(addr++);
      if(c == 0xAA)
      {
        ptr = (uint8_t*)&lcd->tp_matrix;
        for(i=0; i < sizeof(CAL_MATRIX); i++)
        {
          *ptr++ = EEPROM.read(addr++);
        }
        return 0;
      }
    
      return 1;
    }
    private:
      MI0283QT9* lcd;
};
#endif
