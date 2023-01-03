#include "VoltageActivity.h"
#include "..\repository\AvrMicroRepository.h"

VoltageActivity::VoltageActivity(AnalogPort** analogPort, float vref, commonsLayer::analogRefMode mode, uint8_t analogPortsNumber) : DeviceActivity(analogPort, vref,mode, analogPortsNumber) {
}


bool VoltageActivity::isVoltageOutOfRange(AvrMicroRepository& mainRepository) {
	if (!(this->isThereAnyAnalogPortOnAlarm(mainRepository))) return false;
	return true;
}

float  VoltageActivity::getAnalogPortVrefVoltage(AvrMicroRepository& mainRepository, uint8_t analogPin)
{
	return (this->getVref() / 1024) * mainRepository.analogReadm(analogPin);
}

char* VoltageActivity::getLipoBatteryGrafBarLevel(AvrMicroRepository& mainRepository, uint8_t analogPortPin)
{
	for (int i = 0; i < this->_analogPortsNumber; i++)
	{
		if (this->analogPort[i]->getPin() == analogPortPin)
		{
			float batteryVoltageLevel = getAnalogPortVrefVoltage(mainRepository, analogPortPin);
			if (batteryVoltageLevel <= 3.25f)
				return "[    ]o";
			if (batteryVoltageLevel <= 3.30f)
				return "[|   ]o";
			if (batteryVoltageLevel <= 3.40f)
				return "[||  ]o";
			if (batteryVoltageLevel <= 3.60f)
				return "[||| ]o";
			if (batteryVoltageLevel <= 5.50f)
				return "[||||]o";
		}
	}
	return "";
}