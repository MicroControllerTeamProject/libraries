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
	bool _isExternalInterruptOn;
	String _batteryLevelGraf;
	float _internalTemperature;
	char _whatIsHappened = 'X';
	uint16_t offSetTemp = 324;
	uint16_t smokeMaxLevel = 1023;
	bool isDataChanged = false;
};

