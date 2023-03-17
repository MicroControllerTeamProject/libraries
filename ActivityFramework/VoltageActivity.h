#pragma once
#include "DeviceActivity.h"
#include "commonsLayer.h"
#include "AnalogPortSensor.h"


class VoltageActivity : public DeviceActivity
{
public:
	VoltageActivity(AvrMicroRepository& avrMicroRepository, AnalogPortSensor& analogPortSensor, float vref, commonsLayer::analogRefMode mode);
	VoltageActivity();
	bool isVoltageOutOfRange(char* portName);
	char* getGrafBarLevel(char* portName, float minValue, float maxValue, float chargeVoltageValue);
	float  getVoltage(char* portName);
};

