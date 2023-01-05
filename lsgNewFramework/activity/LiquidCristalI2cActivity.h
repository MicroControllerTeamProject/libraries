#pragma once
#include "DeviceActivity.h"
#include "..\repository\LiquidCristalI2CRepository.h"


class LiquidCristalI2cActivity 
{
public:
	LiquidCristalI2cActivity(LiquidCristalI2CRepository* liquidCristalI2CRepository, uint8_t cols, uint8_t rows);
	void print(char* message, uint8_t col, uint8_t row, bool clearBefore);
	void printScroll(char* message, uint8_t col, uint8_t row, bool clearBefore,unsigned long velocity);
private:
	LiquidCristalI2CRepository* liquidCristalI2CRepository;
};

