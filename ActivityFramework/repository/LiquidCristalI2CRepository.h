#pragma once
#include <stdint.h>
class LiquidCristalI2CRepository
{
public:
	LiquidCristalI2CRepository::LiquidCristalI2CRepository(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs,
        uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
        uint8_t backlighPin, uint8_t pol);
    LiquidCristalI2CRepository();
    ~LiquidCristalI2CRepository();
    virtual void Init(uint8_t cols, uint8_t rows);
    virtual void print(char* message, uint8_t col, uint8_t row, bool clearBefore, unsigned long delayDisplay);
    virtual void printSlideMessage(char* message, uint8_t col, uint8_t row, bool clear,unsigned long velocity);
   
    
private:
   
};

