#include "CurrentSensor.h"
#include <Arduino.h>
#include <pins_arduino.h> 

CurrentSensor::CurrentSensor(int analogicSegnalPinIn,
	float analogicAllarmMaxValue,
	float analogicAllarmMinValue,char* uid) :AnalogicSensor(analogicSegnalPinIn, analogicAllarmMaxValue, analogicAllarmMinValue,uid)
{
	_analogicPinIn = analogicSegnalPinIn;
	SetIsSentSMSAllarm(false);
}

CurrentSensor::~CurrentSensor()
{

}

float CurrentSensor::AnalogicRead()
{
	float average = 0;
	for (int i = 0; i < 1000; i++) {
		//It's ok for 5A with sensity 185
		//average = average + (.0264 * analogRead(A0) - 13.51) / 1000;
		//It's ok for 20A with sensity 100
		average = average + (.049 * analogRead(_analogicPinIn) - 25) / 1000;
		delay(1);
	}
	return average;
}

//Make sense if you set min value under the normal
bool  CurrentSensor::IsSensorWorking()
{
		if (IsAnalogicValueOutOfRange())
		{
			SetLastComunication("could be damaged");
			return false;
		}
		else
		{
			SetLastComunication("seems ok");
			return true;
		}
}


bool CurrentSensor::IsCurrentTooHigh()
{
	return IsCurrentTooHigh(GetSegnalValue());
}

bool CurrentSensor::IsCurrentTooHigh(float currentValue)
{
	const bool isTooHigh = currentValue >= GetMaxValue();
	SetLastComunication(isTooHigh ? "is too high" : "seems ok");
	return isTooHigh;
}

bool CurrentSensor::IsCurrentTooLow()
{
	return IsCurrentTooLow(GetSegnalValue());
}

bool CurrentSensor::IsCurrentTooLow(float currentValue)
{
	const bool isTooLow = currentValue <= GetMinValue();
	SetLastComunication(isTooLow ? "is too low" : "seems ok");
	return isTooLow;
}
