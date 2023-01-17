#pragma once

#include "..\interfaces\II2CObjectSensor.h"
class I2COstacleSensor //: public II2CObjectSensor
{
public:
	I2COstacleSensor(uint8_t address, char* uid);
	 char* getUid();
	 uint16_t getAddress();
	 void enable(bool isEnable);
	bool isEnable();
	uint8_t _address;
	char* _uid;
	bool _isEnable = true;
};

