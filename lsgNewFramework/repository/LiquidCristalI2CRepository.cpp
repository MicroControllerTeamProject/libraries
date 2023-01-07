#include "LiquidCristalI2CRepository.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C* _lcd;
LiquidCristalI2CRepository::LiquidCristalI2CRepository(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
    uint8_t backlighPin, uint8_t pol){

    _lcd = new LiquidCrystal_I2C(lcd_Addr, En, Rw, Rs, d4, d5, d6, d7, backlighPin, pol);
}

LiquidCristalI2CRepository::LiquidCristalI2CRepository(){
}

LiquidCristalI2CRepository::~LiquidCristalI2CRepository()
{
    delete(_lcd);
}

void LiquidCristalI2CRepository::Init(uint8_t cols, uint8_t rows)
{
    Wire.begin();
    _lcd->begin(cols, rows);   // iInit the LCD for 16 chars 2 lines
    _lcd->backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
}


void LiquidCristalI2CRepository::print(char* message, uint8_t col, uint8_t row, bool clear)
{
    if (clear) _lcd->clear();
    _lcd->setCursor(col, row); //First line
    _lcd->print(message);
}

void LiquidCristalI2CRepository::printSlideMessage(char* message, uint8_t col, uint8_t row, bool clear, unsigned long velocity)
{
    if(clear) _lcd->clear();
    _lcd->setCursor(col, row); //First line
    _lcd->scrollDisplayLeft();
    _lcd->autoscroll();

    for (int thisChar = 0; thisChar < strlen(message); thisChar++) {
        _lcd->print(message[thisChar]);
        delay(velocity);
    }

    for (int thisChar = 0; thisChar < 16; thisChar++) {
        _lcd->print(" ");
        delay(velocity);
    }
 
}



