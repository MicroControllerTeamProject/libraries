#pragma once
#include "AnalogicSensor.h"
#include "ISensor.h"
class SmokeSensor : 
	public AnalogicSensor, public ISensor
{
public:
	SmokeSensor(int analogicSegnalPinIn,
		float analogicAllarmMaxValue,
		float analogicAllarmMinValue,
		char* uid);
	bool IsSensorWorking();

	bool ThereIsSmoke();
	~SmokeSensor();
};

