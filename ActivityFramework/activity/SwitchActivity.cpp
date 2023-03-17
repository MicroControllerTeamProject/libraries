#include "SwitchActivity.h"

SwitchActivity::SwitchActivity(AvrMicroRepository& avrMicroRepository,DigitalPort** digitalPort) :DeviceActivity(avrMicroRepository,digitalPort) {
}

bool SwitchActivity::isThereASwitchOn()
{
	return this->isThereAnyDigitalPortOnAlarm();
}

bool SwitchActivity::isSwitchOn(char* portName)
{
	return this->isDigitalPortOnAlarm(portName);
}

bool SwitchActivity::isSwitchOn(uint8_t pinNumber)
{
	return false;
}
