#pragma once
#include "..\repository\AvrMicroRepository.h"

class AnalogPort
{
public:
	AnalogPort(const char uid[6], const uint8_t pin);
	bool	isEnable = true;
	bool	isOnError = false;
	uint16_t digitalValue = 0;
	float	 analogVrefValue = 0;
	float	maxVoltageAlarmValueIn = 0;
	float	minVoltageAlarmValueIn = 0;
	uint16_t	 maxAlarmValueIn = 0;
	uint16_t	 minAlarmValueIn = 0;
	float unitOfMisureFullScale = 0;
	float maxUnitOfMisureAlarmValue = 0;
	float minUnitOfMisureAlarmValue = 0;
	const char* getUid();
	uint8_t getPin();
private:
	const char* _uid = {};
	uint8_t _pin;
};
