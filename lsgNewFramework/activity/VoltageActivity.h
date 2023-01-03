#pragma once
#include "DeviceActivity.h"
#include "..\commons\commonsLayer.h"

class VoltageActivity : public DeviceActivity
{
public:
	VoltageActivity(AnalogPort** analogPort, float vref, commonsLayer::analogRefMode mode, uint8_t analogPortsNumber);
	bool isVoltageOutOfRange(AvrMicroRepository& mainRepository);
	char* getLipoBatteryGrafBarLevel(AvrMicroRepository& mainRepository, uint8_t analogPortPin);
	float  getAnalogPortVrefVoltage(AvrMicroRepository& mainRepository, uint8_t analogPin);
};

