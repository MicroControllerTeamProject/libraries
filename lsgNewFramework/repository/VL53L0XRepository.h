#pragma once
#include <stdint.h>
#include "..\repository\AvrMicroRepository.h"


class VL53L0XRepository : public AvrMicroRepository
{
public:
	VL53L0XRepository();
	void init(uint8_t address);
	uint16_t getMillimetersDistance();
	uint8_t getAddress();
	bool isSensorOnError();
	
	
protected:
private:
	bool _isSensorOnError;
};

