#include "SmokeActivity.h"
#include "..\repository\AvrMicroRepository.h"

SmokeActivity::SmokeActivity(AnalogPort** analogPort,float vref, commonsLayer::analogRefMode mode,uint8_t analogPortsNumber)  : DeviceActivity(analogPort,vref,mode,analogPortsNumber){
}

bool SmokeActivity::isThereSmoke(AvrMicroRepository& avrMicroRepository)
{
	return this->isThereAnyAnalogPortOnAlarm(avrMicroRepository);
}