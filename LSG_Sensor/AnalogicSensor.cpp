
#include "AnalogicSensor.h"

AnalogicSensor::AnalogicSensor(char* uid)
{
	_uid = uid;
}

AnalogicSensor::AnalogicSensor(int analSignalPin, float analogicAllarmMaxValue, float analogicAllarmMinValue,char* uid)
{
	_analSignalPin = analSignalPin;
	_maxValue = analogicAllarmMaxValue;
	_minValue = analogicAllarmMinValue;
	_uid = uid;

	AnalogicSensor(_analSignalPin, 0, _maxValue, _minValue,_uid);
}


AnalogicSensor::AnalogicSensor(uint8_t digitalSegnalPinIn, float analogicAllarmMaxValue, float analogicAllarmMinValue,char* uid)
{
	_digitalSignalPin = digitalSegnalPinIn;
	pinMode(digitalSegnalPinIn, INPUT);
	_maxValue = analogicAllarmMaxValue;
	_minValue = analogicAllarmMinValue;
	_uid = uid;

	AnalogicSensor(0, _digitalSignalPin, _maxValue, _minValue,_uid);
}


AnalogicSensor::AnalogicSensor(int analSignalPin, uint8_t digitalSegnalPinIn, float analogicAllarmMaxValue, float analogicAllarmMinValue, char* uid)
{
	if (analSignalPin != 0)
	{
		_analSignalPin = analSignalPin;
	}
	if (digitalSegnalPinIn != 0)
	{
		_digitalSignalPin = digitalSegnalPinIn;
		pinMode(digitalSegnalPinIn, INPUT);
	}
	_maxValue = analogicAllarmMaxValue;
	_minValue = analogicAllarmMinValue;
	_uid = uid;
}

AnalogicSensor::~AnalogicSensor(){}
float AnalogicSensor::GetMinValue(){ return _minValue;}
float AnalogicSensor::GetMaxValue(){ return _maxValue; }
uint8_t AnalogicSensor::GetAnalogicSignalPin(){ return _analSignalPin; }


bool AnalogicSensor::IsDigitalSegnalPinOn(){
	return digitalRead(_digitalSignalPin);
}

void AnalogicSensor::SetDigitalAlarmPinOut(int alarmPin){ 
	pinMode(alarmPin, OUTPUT);
	_alarmPin = alarmPin;
}

void AnalogicSensor::AllarmPinOn(unsigned long time){
	digitalWrite(_alarmPin, HIGH);
	delay(time);
	digitalWrite(_alarmPin, LOW);
}

void AnalogicSensor::AllarmPinOn(){
	digitalWrite(_alarmPin, HIGH);
}
void AnalogicSensor::AllarmPinOff(){
	digitalWrite(_alarmPin, LOW);
}

uint8_t AnalogicSensor::IsAllarmPinOn(){
	return digitalRead(_alarmPin);
}

float AnalogicSensor::GetSegnalValue()
{
	_sensorValue = AnalogicRead();
	return _sensorValue;
}

float AnalogicSensor::AnalogicRead()
{
	return analogRead(_analSignalPin);
}


bool AnalogicSensor::IsAnalogicValueOutOfRange()
{
	if (_sensorValue >= _maxValue || _sensorValue <= _minValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AnalogicSensor::IsDigitOnAndValueOutOfRange()
{
	if (_digitalSignalPin != -1)
	{
		if (!digitalRead(_digitalSignalPin))
			return true;
	}

	if (_digitalSignalPin != -1)
	{
		_sensorValue = analogRead(_digitalSignalPin);

		if (_sensorValue > _maxValue || _sensorValue < _minValue)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool AnalogicSensor::IsDownValue()
{
	_sensorValue = analogRead(_analSignalPin);
	if (_sensorValue < _minValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}


char* AnalogicSensor::UID()
{
	return _uid;
}

void AnalogicSensor::SetLastComunication(char* lastComunication)
{
	char message[100];   // array to hold the result.
	/*char* message2;*/
	strcpy(message, UID()); // copy string one into the result.
	strcat(message, " "); // append string two to the result.
	strcat(message, lastComunication);
	/*message2 = message;*/
	_lastComunication = message;
	

}

char* AnalogicSensor::GetLastComunication()
{
	return _lastComunication;
}



