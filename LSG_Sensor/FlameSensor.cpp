#include "FlameSensor.h"
#include <arduino.h>
#include <pins_arduino.h> 



FlameSensor::FlameSensor(int analogicSegnalPinIn, 
	int digitalSegnalPinIn, 
	float analogicAllarmMaxValue, 
	float analogicAllarmMinValue,char* uid) :AnalogicSensor(analogicSegnalPinIn, digitalSegnalPinIn, analogicAllarmMaxValue, analogicAllarmMinValue,uid)
{
	SetIsSentSMSAllarm(false);
}


FlameSensor::~FlameSensor()
{
}

//float FlameSensor::GetAnalogicValue()
//{
//	return GetSegnalValue();
//}



bool  FlameSensor::IsSensorWorking()
{
	
	//Digital signal of flame sensor is Low when flames are detected , High when aren't flames
	if ((GetSegnalValue() < GetMinValue() && IsDigitalSegnalPinOn() == HIGH) || (GetSegnalValue() > GetMinValue() && IsDigitalSegnalPinOn() == LOW))
	{
		//_lastComunication = "Flame sensor is not working";
		SetLastComunication("sensor is not working");
		return false;
	}
	else
	{
		//_lastComunication = "Flame sensor is working";
		SetLastComunication("sensor is working");
		return true;
	}
}


bool FlameSensor::ThereAreFlames()
{
	if (/*IsDigitOnAndValueOutOfRange() &&*/
		GetSegnalValue() < 950 /*&&
		!IsDigitalSegnalPinOn()*/)
	{
		//_lastComunication = "Flames in garage";
		SetLastComunication("flames in the local");
		return true;

	}
	else
		//_lastComunication = "NO Flames in garage";
		SetLastComunication("NO flames in the local");
		return false;
}
