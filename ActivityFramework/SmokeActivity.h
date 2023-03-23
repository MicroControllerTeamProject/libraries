#pragma once
#include "DeviceActivity.h"
#include "commonsLayer.h"
#include "AnalogPortSensor.h"

class SmokeActivity : public DeviceActivity
{
public:
	SmokeActivity(AvrMicroRepository& avrMicroRepository, AnalogPortSensor& analogPortSensor, float vref, commonsLayer::analogRefMode mode);
	SmokeActivity();
	bool isThereSmoke(char* analogPortUid);
};

