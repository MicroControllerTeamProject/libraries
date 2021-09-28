#pragma once
#include <Arduino.h>
#include <pins_arduino.h>

class TransfertObject
{
public:
	TransfertObject();
	bool isSystemActivated;
	float batteryVoltage;
	bool isBuzzerON = 0;
	bool isExternalInterruptOn;
	String batteryLevelGraf;
	float internalTemperature;
	char whatIsHappened = 'X';
	uint16_t offSetTemp = 324;
	uint16_t smokeMaxLevel = 1023;
	uint8_t internalTemperatureMaxValue = 40;
	bool isDataChanged = false;
	bool isActiveDebug = false;
};

