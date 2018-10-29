#pragma once
#include <arduino.h>
#include <pins_arduino.h> 

class PrintSerialAndLCDFunctions
{
public:
	PrintSerialAndLCDFunctions();
	~PrintSerialAndLCDFunctions();
	void WriteSimpleMessage(uint8_t lcdcolumn, uint8_t lcdrow, char* message, bool isLcdClear,int delaySeconds);
	void WriteSimpleMessage(char* message, bool isLcdClear, int delaySeconds);
	void WriteComplexMessage(char* message, float misure, bool isLcdClear,int delaySeconds);
	void WriteComplexMessage(uint8_t lcdcolumn, uint8_t lcdrow, char* message, float misure, bool isLcdClear,int delaySeconds);
	void LCDBegin(uint8_t col, uint8_t row);

};

