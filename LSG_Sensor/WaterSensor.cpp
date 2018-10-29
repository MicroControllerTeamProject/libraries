#include "WaterSensor.h"


WaterSensor::WaterSensor(int analogicSegnalPinIn,
	float analogicAllarmMaxValue,
	float analogicAllarmMinValue,char* uid) :AnalogicSensor(analogicSegnalPinIn, analogicAllarmMaxValue, analogicAllarmMinValue,uid)
{
	SetIsSentSMSAllarm(false);
}


WaterSensor::~WaterSensor()
{
}



bool WaterSensor::IsSensorWorking()
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

bool WaterSensor::IsThereWater()
{
	if (GetSegnalValue() > GetMaxValue())
	{
		SetLastComunication("Water in the garage");
		return true;
	}
	else
	{
		SetLastComunication("No Water in the garage");
		return false;
	}
}
