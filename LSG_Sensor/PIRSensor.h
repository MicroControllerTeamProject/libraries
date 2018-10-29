#pragma once
#include <AnalogicSensor.h>
#include <ISensor.h>
class PIRSensor :
	public AnalogicSensor,  public ISensor
{
public:
	PIRSensor(int analogicSegnalPinIn,
		int digitalSegnalPinIn,
		float analogicAllarmMaxValue,
		float analogicAllarmMinValue,
		char* uid);
	bool isHumanDetected();
	bool IsSensorWorking();

	~PIRSensor();
};

