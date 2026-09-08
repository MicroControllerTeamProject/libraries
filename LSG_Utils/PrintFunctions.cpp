#include "PrintFunctions.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>  
#include "OneWire.h"


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

void PrintSerialAndLCDFunctions::WriteSimpleMessage(uint16_t lcdcolumn, uint16_t lcdrow, char* message, bool isLcdClear,int delaySeconds)
{
	if (isLcdClear)
	{
		_lcd2.clear();
	}
	// 256 indica che il chiamante non richiede un cambio di cursore.
	if (lcdcolumn < 256 && lcdrow < 256)
	{
		_lcd2.setCursor((uint8_t)lcdcolumn, (uint8_t)lcdrow);
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

void PrintSerialAndLCDFunctions::WriteComplexMessage(uint16_t lcdcolumn, uint16_t lcdrow, char* message, float misure, bool isLcdClear,int delaySeconds)
{

	
	if (isLcdClear)
	{
		_lcd2.clear();
	}
	// 256 indica che il chiamante non richiede un cambio di cursore.
	if (lcdcolumn < 256 && lcdrow < 256)
	{
		_lcd2.setCursor((uint8_t)lcdcolumn, (uint8_t)lcdrow);
	}
	_lcd2.print(message); _lcd2.print(":"); _lcd2.print(misure);

	delay(delaySeconds * 1000);

}


