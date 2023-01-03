#pragma once
#include "DeviceActivity.h"

class PirActivity : public DeviceActivity
{
public:
	PirActivity(DigitalPort** digitalPort, uint8_t digitalPortsNumber);
	bool isThereAnyOne(AvrMicroRepository& avrMicroRepository);
};

