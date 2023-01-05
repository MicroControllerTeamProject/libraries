#pragma once
#include "DeviceActivity.h"
class SwitchActivity :
    public DeviceActivity
{
public:
    SwitchActivity::SwitchActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** digitalPort, uint8_t digitalPortsNumber);
    bool isThereASwitchOn();
};

