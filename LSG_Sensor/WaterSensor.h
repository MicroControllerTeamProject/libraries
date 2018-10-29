#pragma once
#include "AnalogicSensor.h"
#include "ISensor.h"
class WaterSensor :
	public AnalogicSensor, public ISensor
{
public:
	WaterSensor(int analogicSegnalPinIn,
		float analogicAllarmMaxValue,
		float analogicAllarmMinValue,
		char* uid);
	bool IsSensorWorking();

	bool IsThereWater();
	~WaterSensor();
};

