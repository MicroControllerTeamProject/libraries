#include "SmokeSensor.h"


SmokeSensor::SmokeSensor(int analogicSegnalPinIn,
	float analogicAllarmMaxValue,
	float analogicAllarmMinValue,char* uid) :AnalogicSensor(analogicSegnalPinIn, analogicAllarmMaxValue, analogicAllarmMinValue,uid)
{
	SetIsSentSMSAllarm(false);
}


SmokeSensor::~SmokeSensor()
{
}



bool SmokeSensor::IsSensorWorking()
{
	if (GetSegnalValue() < GetMinValue())
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


bool SmokeSensor::ThereIsSmoke()
{
	if (GetSegnalValue() > GetMaxValue())
	{
		SetLastComunication("Smoke in garage");
		return true;
	}
	else
	{
		SetLastComunication("No Smoke in garage");
		return false;
	}
}
