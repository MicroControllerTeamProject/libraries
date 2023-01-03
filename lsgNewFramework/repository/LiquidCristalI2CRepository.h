#pragma once
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LiquidCristalI2CRepository
{
public:
	LiquidCristalI2CRepository::LiquidCristalI2CRepository(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs,
        uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
        uint8_t backlighPin, uint8_t pol);
    void Init(uint8_t cols, uint8_t rows);
    void print(char* message, uint8_t col, uint8_t row, bool clear);
    LiquidCristalI2CRepository();
    ~LiquidCristalI2CRepository();
private:
    LiquidCrystal_I2C* lcd;
};

