#pragma once
#include "DeviceActivity.h"
#include "..\commons\commonsLayer.h"

class SmokeActivity : public DeviceActivity
{
public:
	SmokeActivity(AnalogPort** analogPort,float vref, commonsLayer::analogRefMode mode, uint8_t analogPortsNumber);
	bool isThereSmoke(AvrMicroRepository& avrMicroRepository);
};

