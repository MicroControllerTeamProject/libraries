#pragma once

#include "..\interfaces\II2CObjectSensor.h"
class I2COstacleSensor : public II2CObjectSensor
{
public:
	I2COstacleSensor(uint8_t address, char* uid);
	virtual char* getUid();
	virtual uint16_t getAddress();
	virtual void enable(bool isEnable);
	virtual bool isEnable();
	uint8_t _address;
	char* _uid;
	bool _isEnable = true;
};

