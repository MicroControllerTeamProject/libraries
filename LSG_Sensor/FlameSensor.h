#pragma once
#include "AnalogicSensor.h"
#include "ISensor.h"
class FlameSensor :
	public AnalogicSensor , public ISensor
{
public:
	FlameSensor(int analogicSegnalPinIn, 
		int digitalSegnalPinIn, 
		float analogicAllarmMaxValue, 
		float analogicAllarmMinValue,
		char* uid);
	~FlameSensor();
	bool  IsSensorWorking();

	bool ThereAreFlames();
};

