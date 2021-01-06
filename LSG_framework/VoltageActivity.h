#pragma once
#include "DeviceActivity.h"

class VoltageActivity : public DeviceActivity
{
public:
	VoltageActivity(AnalogPort** analogPort, float vref, uint8_t digitalPortsNumber);
	bool isVoltageOutOfRange();
};

