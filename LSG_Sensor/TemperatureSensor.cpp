#include <TemperatureSensor.h>
#include <DallasTemperature.h>
#include <OneWire.h>


//OneWire _oneWire(_digitalPin);
//DallasTemperature _sensor(&_oneWire);

TemperatureSensor::TemperatureSensor(uint8_t digitalSegnalPinIn, 
	float analogicAllarmMaxValue, 
	float analogicAllarmMinValue,char* uid) : AnalogicSensor(digitalSegnalPinIn, analogicAllarmMaxValue, analogicAllarmMinValue,uid)
{
	_digitalPin = digitalSegnalPinIn;
	SetIsSentSMSAllarm(false);
}



TemperatureSensor::~TemperatureSensor()
{
	
}

float TemperatureSensor::AnalogicRead()
{
	return _tempC;
}


float TemperatureSensor::GetSegnalValue(DeviceAddress probe, uint8_t resolution)
{
	OneWire oneWire(_digitalPin);
	DallasTemperature sensor(&oneWire);
	sensor.setResolution(probe,resolution);
	sensor.begin();
	sensor.requestTemperatures();
	_tempC = sensor.getTempC(probe);
	AnalogicSensor::GetSegnalValue();
}


bool  TemperatureSensor::IsSensorWorking()
{
	if (IsAnalogicValueOutOfRange())
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


//float TemperatureSensor::GetAnalogicValue(DeviceAddress probe, DallasTemperature sensor)
//{
//
//	float tempC = sensor.getTempC(probe);
//
//	//if (tempC == -127.00)
//	//{
//	//	Serial.print("Error getting temperature  ");
//	//}
//		//Serial.print("C: ");
//		//Serial.print(tempC);
//		///*Serial.print(" F: ");
//		//Serial.print(DallasTemperature::toFahrenheit(tempC));*/
//	return tempC;
//}

