#include "SwitchActivity.h"

SwitchActivity::SwitchActivity(AvrMicroRepository& avrMicroRepository,DigitalPort** digitalPort, uint8_t digitalPortsNumber) :DeviceActivity(avrMicroRepository,digitalPort, digitalPortsNumber) {
}

bool SwitchActivity::isThereASwitchOn()
{
	return this->isThereAnyDigitalPortOnAlarm();
}
