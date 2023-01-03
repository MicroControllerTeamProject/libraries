#include "LiquidCristalI2cActivity.h"


LiquidCristalI2cActivity::LiquidCristalI2cActivity(LiquidCristalI2CRepository* liquidCristalI2CRepository,uint8_t cols, uint8_t rows)// : DeviceActivity()
{
	this->liquidCristalI2CRepository = liquidCristalI2CRepository;
	this->liquidCristalI2CRepository->Init(cols,rows);
}

void LiquidCristalI2cActivity::print(char* message, uint8_t col, uint8_t row, bool clearBefore)
{
	this->liquidCristalI2CRepository->print(message, col, row, clearBefore);
}
