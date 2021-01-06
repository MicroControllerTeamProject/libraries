#include "CurrentActivity.h"
CurrentActivity::CurrentActivity(AnalogPort** analogPort,
	float vref, 
	uint8_t analogPortsNumber
) : DeviceActivity(analogPort, vref, analogPortsNumber)
{
	this->maxAmpereAlarm = maxAmpereAlarm;
	this->minAmpereAlarm = minAmpereAlarm;
}

float CurrentActivity::ampereRead(String portName)
{
	/*for (int i = 0; i < this->analogPortsNumber; i++)
	{
		if (this->analogPort[i]->getUid() == portName)
		{*/
			return getUnitOfMisureValue(portName);
			//return (limitPortAmpere / 1023) * analogRead(this->analogPort[i]->pin);
	/*	}
	}*/
}

float CurrentActivity::ampereRead(AnalogPort* analogPort)
{
	
}


//bool CurrentActivity::isAmpereOnAlarm(uint8_t limitSensorAmpere, 
//	uint8_t maxAmpereForAlarm, 
//	uint8_t minAmpereForAlarm, 
//	AnalogPort* analogPort)
//{
//
//}

//bool CurrentActivity::isAmpereOnAlarm(uint8_t limitSensorAmpere,
//	uint8_t maxAmpereForAlarm,
//	uint8_t minAmpereForAlarm  
//	/*String portName*/)
//{
//	for (int i = 0; i < this->analogPortsNumber; i++)
//	{
//		if (((limitSensorAmpere / 1023) * analogRead(analogPort[i]->pin)) < minAmpereAlarm )
//		{
//			this->lastAlarmDescription = analogPort[i]->uid + " current level too LOW";
//			this->lastAlarmCode = 'L';
//			return true;
//		}
//		else if (((limitSensorAmpere / 1023) * analogRead(analogPort[i]->pin)) > maxAmpereAlarm)
//		{
//			this->lastAlarmDescription = analogPort[i]->uid + " current level too HIGH";
//			this->lastAlarmCode = 'H';
//			return true;
//		}
//	}
//	return false;
//}


