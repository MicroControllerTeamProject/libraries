#include <VoltageSensor.h>


VoltageSensor::VoltageSensor(int analogicSegnalPinIn,
	float analogicAllarmMaxValue,
	float analogicAllarmMinValue, float voltageReference,char* uid) : AnalogicSensor(analogicSegnalPinIn, analogicAllarmMaxValue, analogicAllarmMinValue, uid)
{
	SetIsSentSMSAllarm(false);
	_voltageReference = voltageReference;
}

VoltageSensor::~VoltageSensor()
{
}

float VoltageSensor::AnalogicRead()
{
	return ReadAnalogicXXValue(AnalogicSensor::GetAnalogicSignalPin());
}

bool VoltageSensor::IsVoltageTooLow()
{
	if (GetSegnalValue() < GetMinValue())
	{
		SetLastComunication("Voltage is right");
		return false;
	}
	else
	{
		SetLastComunication("low Voltage");
		return true;
	}
}

bool VoltageSensor::IsSensorWorking()
{
	if (IsAnalogicValueOutOfRange())
	{
		SetLastComunication("could be damaged");
		return true;
	}
	else
	{
		SetLastComunication("seems ok");
		return false;
	}
}

float VoltageSensor::ReadAnalogicXXValue(uint8_t analogicPort)
{
	/*Serial.println("Lettura Analogica xxValue");*/
	uint8_t num_samples = 5; // 10 o 25
	uint8_t bits_of_precision; //bits of precision for the ADC (Analog to Digital Converter)
	float analog_reading; //the ADC reading
	//16-bit ADC reading
	bits_of_precision = 16; //bits of precision for the ADC (Analog to Digital Converter)
	analog_reading = adc.analogReadXXbit(analogicPort, bits_of_precision, num_samples); //get the avg. of [num_samples] 16-bit readings
	return (analog_reading / MAX_READING_16_bit*_voltageReference);
}
