#pragma once
#include <stdint.h>

class VL53L0XRepository 
{
public:
	VL53L0XRepository();
	virtual void initContinuos(uint8_t address);
	virtual void init(uint8_t address);
	virtual uint16_t getMillimetersDistance();
	virtual uint8_t getAddress();
	virtual void setAddress(uint8_t address);
	virtual bool isSensorOnError();
	
protected:
private:
	bool _isSensorOnError;
};

