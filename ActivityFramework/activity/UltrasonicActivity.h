#pragma once
#include "DeviceActivity.h"
#include "..\repository\UltrasonicRepository.h"

class UltrasonicActivity : public DeviceActivity
{
public:
	UltrasonicActivity(DigitalPort** digitalPort, uint8_t digitalPortsNumber, char* triggerPortName, char* echoPortName, unsigned long timeOut);
	//unsigned int getDistance(String triggerPortName, String echoPortName);
	
	char* triggerPortName;
	char* echoPortName;
	unsigned long timeOut;
	unsigned int getDistance(UltrasonicRepository& ultrasonicRepository);
	//float getUnitOfMisureValue(UltrasonicRepository& ultrasonicRepository);

private:

	
};

