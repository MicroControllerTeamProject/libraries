#include "LiquidCristalI2CRepository.h"


LiquidCristalI2CRepository::LiquidCristalI2CRepository(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
    uint8_t backlighPin, uint8_t pol){

    this->lcd = new LiquidCrystal_I2C(lcd_Addr, En, Rw, Rs, d4, d5, d6, d7, backlighPin, pol);
}

LiquidCristalI2CRepository::LiquidCristalI2CRepository(){
}

LiquidCristalI2CRepository::~LiquidCristalI2CRepository()
{
    delete(this->lcd);
}

void LiquidCristalI2CRepository::Init(uint8_t cols, uint8_t rows)
{
    Wire.begin();
    this->lcd->begin(cols, rows);   // iInit the LCD for 16 chars 2 lines
    this->lcd->backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
}


void LiquidCristalI2CRepository::print(char* message, uint8_t col, uint8_t row, bool clear)
{
    if (clear) lcd->clear();
    this->lcd->setCursor(col, row); //First line
    this->lcd->print(message);
}

void LiquidCristalI2CRepository::printSlideMessage(char* message, uint8_t col, uint8_t row, bool clear, unsigned long velocity)
{
    if(clear) this->lcd->clear();
    this->lcd->setCursor(col, row); //First line
    this->lcd->scrollDisplayLeft();
    this->lcd->autoscroll();

    for (int thisChar = 0; thisChar < strlen(message); thisChar++) {
        this->lcd->print(message[thisChar]);
        delay(velocity);
    }

    for (int thisChar = 0; thisChar < 16; thisChar++) {
        this->lcd->print(" ");
        delay(velocity);
    }
 
}



