#pragma once
#include "DeviceActivity.h"
#include "..\commons\commonsLayer.h"

class VoltageActivity : public DeviceActivity
{
public:
	VoltageActivity(AvrMicroRepository& avrMicroRepository, AnalogPortSensor** _listOfAnalogPortSensor, float vref, commonsLayer::analogRefMode mode, uint8_t analogPortSensorsNumber);
	bool isVoltageOutOfRange(char* portName);
	char* getGrafBarLevel(char* portName, float minValue, float maxValue);
	float  getVoltage(char* portName);
};

