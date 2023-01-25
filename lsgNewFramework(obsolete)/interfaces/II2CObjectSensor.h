#pragma once
#include <stdint.h>

class II2CObjectSensor
{
public:
	virtual ~II2CObjectSensor() {}
	virtual void setAddress(uint8_t address) = 0;
	virtual void setUid(char* uid) = 0;
	virtual char* getUid() = 0;
	virtual uint16_t getAddress() = 0;
	virtual void enable(bool isEnable) = 0;
	virtual bool isEnable() = 0;
};