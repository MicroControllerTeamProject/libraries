#pragma once
#include "DeviceActivity.h"

class RelayActivity : public DeviceActivity
{
public:
	RelayActivity(DigitalPort** digitalPort, uint8_t digitalPortsNumber);
};



