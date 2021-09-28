#include "VoltageActivity.h"

VoltageActivity::VoltageActivity(AnalogPort** analogPort, float vref, uint8_t mode, uint8_t digitalPortsNumber) : DeviceActivity(analogPort, vref,mode, digitalPortsNumber) {
}
bool VoltageActivity::isVoltageOutOfRange(){
	if (this->isThereAnyAnalogPortOnAlarm())
	{
		return true;
	}
	else { return false; 
	}
}