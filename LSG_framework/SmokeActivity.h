#pragma once
#include "DeviceActivity.h"

class SmokeActivity : public DeviceActivity
{
public:
	SmokeActivity(AnalogPort** analogPort,float vref, uint8_t analogPortsNumber);
	bool isThereSmoke();
};

