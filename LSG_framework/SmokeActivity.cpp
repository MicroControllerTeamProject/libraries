#include "SmokeActivity.h"

SmokeActivity::SmokeActivity(AnalogPort** analogPort,float vref, uint8_t mode,uint8_t analogPortsNumber)  :
	DeviceActivity(analogPort,vref,mode,analogPortsNumber){
}

bool SmokeActivity::isThereSmoke()
{
	return this->isThereAnyAnalogPortOnAlarm();
}