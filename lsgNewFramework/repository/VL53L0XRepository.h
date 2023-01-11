#pragma once
#include <VL53L0X.h>
#include <stdint.h>
class VL53L0XRepository
{
public:
	VL53L0XRepository();
	uint16_t getMillimetersDistance();
	bool isSensorOnError();
protected:
private:
	bool _isSensorOnError;
};

