#pragma once
#include "DeviceActivity.h"
class CurrentActivity : public DeviceActivity
{
public:
	CurrentActivity(AnalogPort** analogPort,
		float vref, 
		uint8_t analogPortsNumber);
	float ampereRead(String portName);
	float ampereRead(AnalogPort* analogPort);
	/*bool isAmpereOnAlarm(uint8_t limitSensorAmpere,
		uint8_t maxAmpereForAlarm,
		uint8_t minAmpereForAlarm);*/
private:
	float maxAmpereAlarm = 0;
	float minAmpereAlarm = 0;
};


