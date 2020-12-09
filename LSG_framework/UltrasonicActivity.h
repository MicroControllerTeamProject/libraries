#pragma once
#include "DeviceActivity.h"


class UltrasonicActivity : public DeviceActivity
{
public:
	UltrasonicActivity(DigitalPort** digitalPort, uint8_t digitalPortsNumber, String triggerPortName, String echoPortName);
	//unsigned int getDistance(String triggerPortName, String echoPortName);
	
	String triggerPortName;
	String echoPortName;
	float getDistance();

private:
	float getUnitOfMisureValue();

};

