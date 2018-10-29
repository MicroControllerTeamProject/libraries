#include "PrintFunctions.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>  
#include <OneWire.h>


LiquidCrystal_I2C _lcd2(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
PrintSerialAndLCDFunctions::PrintSerialAndLCDFunctions()
{
}

PrintSerialAndLCDFunctions::~PrintSerialAndLCDFunctions()
{
}

void PrintSerialAndLCDFunctions::LCDBegin(uint8_t col, uint8_t row)
{
	_lcd2.begin(col, row);
}

void PrintSerialAndLCDFunctions::WriteSimpleMessage(uint8_t lcdcolumn, uint8_t lcdrow, char* message, bool isLcdClear,int delaySeconds)
{
	Serial.println(message);
	if (lcdcolumn != 256)
		_lcd2.setCursor(lcdcolumn, lcdrow);
	if (isLcdClear)
	{
		_lcd2.clear();
	}
	_lcd2.print(message);
	delay(delaySeconds * 1000);
}


void PrintSerialAndLCDFunctions::WriteSimpleMessage(char* message, bool isLcdClear, int delaySeconds)
{
	WriteSimpleMessage(256, 256, message, isLcdClear, delaySeconds);
}

void PrintSerialAndLCDFunctions::WriteComplexMessage(char* message, float misure, bool isLcdClear,int delaySeconds)
{
	WriteComplexMessage(256, 256, message, misure, isLcdClear, delaySeconds);
}

void PrintSerialAndLCDFunctions::WriteComplexMessage(uint8_t lcdcolumn, uint8_t lcdrow, char* message, float misure, bool isLcdClear,int delaySeconds)
{
	Serial.print(message); Serial.print(":"); Serial.println(misure);

	if (lcdcolumn != 256)
	{
		_lcd2.setCursor(lcdcolumn, lcdrow);
	}
	
	if (isLcdClear)
	{
		_lcd2.clear();
	}
	_lcd2.print(message); _lcd2.print(":"); _lcd2.print(misure);

	delay(delaySeconds * 1000);

}


