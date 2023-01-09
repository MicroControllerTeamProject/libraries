#include "SwitchActivity.h"

SwitchActivity::SwitchActivity(AvrMicroRepository& avrMicroRepository,DigitalPort** digitalPort, uint8_t digitalPortsNumber) :DeviceActivity(avrMicroRepository,digitalPort, digitalPortsNumber) {
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
