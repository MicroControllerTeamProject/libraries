#include "SmokeActivity.h"
#include "AvrMicroRepository.h"
#include <stdlib.h>
#include <string.h>


SmokeActivity::SmokeActivity(AvrMicroRepository& avrMicroRepository, AnalogPortSensor& analogPortSensor, float vref, commonsLayer::analogRefMode mode)
	: DeviceActivity(avrMicroRepository, analogPortSensor, vref, mode){
}

SmokeActivity::SmokeActivity()
{
}

bool SmokeActivity::isThereSmoke(char* analogPortUid)
{

	if (!(this->isAnalogPortOnAlarm(analogPortUid))) return false;
	return true;
}