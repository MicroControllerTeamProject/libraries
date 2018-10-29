#pragma once
#include <AnalogicSensor.h>
#include <ISensor.h>
#include <eRCaGuy_analogReadXXbit.h>

const float MAX_READING_10_bit = 1023.0;
const float MAX_READING_11_bit = 2046.0;
const float MAX_READING_12_bit = 4092.0;
const float MAX_READING_13_bit = 8184.0;
const float MAX_READING_14_bit = 16368.0;
const float MAX_READING_15_bit = 32736.0;
const float MAX_READING_16_bit = 65472.0;
const float MAX_READING_17_bit = 130944.0;
const float MAX_READING_18_bit = 261888.0;
const float MAX_READING_19_bit = 523776.0;
const float MAX_READING_20_bit = 1047552.0;
const float MAX_READING_21_bit = 2095104.0;



class VoltageSensor : 
	public AnalogicSensor, public ISensor
{
public:
	VoltageSensor(int analogicSegnalPinIn,
		float analogicAllarmMaxValue,
		float analogicAllarmMinValue,
		float voltageReference,
		char* uid);
	bool IsVoltageTooLow();
	bool IsSensorWorking();
	float AnalogicRead();
	float ReadAnalogicXXValue(uint8_t analogicPort);
	~VoltageSensor();
private:
		eRCaGuy_analogReadXXbit adc;
		float _voltageReference;
};

