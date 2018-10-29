#include "PIRSensor.h"
#include <arduino.h>
#include <pins_arduino.h> 


PIRSensor::PIRSensor(int analogicSegnalPinIn,
	int digitalSegnalPinIn,
	float analogicAllarmMaxValue,
	float analogicAllarmMinValue, char* uid) : AnalogicSensor(analogicSegnalPinIn, digitalSegnalPinIn, analogicAllarmMaxValue, analogicAllarmMinValue, uid)
{
	SetIsSentSMSAllarm(false);
}

bool PIRSensor::isHumanDetected()
{
	if (AnalogicSensor::IsDigitalSegnalPinOn())
	{
		return true;
	}
	else 
	{
		return false;
	}
}


bool PIRSensor::IsSensorWorking()
{
	return true;
}

PIRSensor::~PIRSensor()
{

}

