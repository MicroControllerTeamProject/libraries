#pragma once
#include "AnalogicSensor.h"
#include "ISensor.h"
#include <DallasTemperature.h>
#include <OneWire.h>
class TemperatureSensor :
	public AnalogicSensor, public ISensor
{
public:
	TemperatureSensor(uint8_t digitalSegnalPinIn, float analogicAllarmMaxValue, float analogicAllarmMinValue,char* uid);
	~TemperatureSensor();
	float GetSegnalValue(DeviceAddress probe, uint8_t resolution);
	bool IsSensorWorking();
protected:
	virtual float AnalogicRead();

	/*float GetAnalogicValue(DeviceAddress deviceAddress, DallasTemperature sensor);*/
private : 
	uint8_t _digitalPin;
	float _tempC;

};



