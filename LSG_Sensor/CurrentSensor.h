#pragma once
#include "AnalogicSensor.h"
#include "ISensor.h"
class CurrentSensor : 
	public AnalogicSensor, public ISensor
{

private:
	int _analogicPinIn;

public:
	CurrentSensor(int analogicSegnalPinIn,
		float analogicAllarmMaxValue,
		float analogicAllarmMinValue,char* uid);
	~CurrentSensor();
	bool  IsSensorWorking();
	float AnalogicRead();
	bool IsCurrentTooHigh();
	bool IsCurrentTooLow();
};

