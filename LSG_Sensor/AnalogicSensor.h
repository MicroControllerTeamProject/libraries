#pragma once
#include <arduino.h>
#include <pins_arduino.h> 
//In and Out specified on all pins are refered to Arduino and not to sensor. 

class AnalogicSensor
{
public:
	AnalogicSensor(char* uid);
	AnalogicSensor(int analSignalPin, float analogicAllarmMaxValue, float analogicAllarmMinValue,char* uid);
	AnalogicSensor(int analSignalPin, uint8_t digitalSegnalPinIn, float analogicAllarmMaxValue, float analogicAllarmMinValue,char* uid);
	AnalogicSensor(uint8_t digitalSegnalPinIn, float analogicAllarmMaxValue, float analogicAllarmMinValue,char* uid);
	~AnalogicSensor();
	float GetMinValue();
	float GetMaxValue();
	
	//Manage a pin for alarm in out
	void SetDigitalAlarmPinOut(int alarmPin);
	bool IsAnalogicValueOutOfRange();
	virtual bool IsDigitOnAndValueOutOfRange();
	//Turn on a pin for alarm in out for a specific time
	void AllarmPinOn(unsigned long time);
	//Turn on a pin for alarm in out 
	void AllarmPinOn();
	//Turn off a pin for alarm in off
	void AllarmPinOff();
	//Check allrm pin.
	uint8_t IsAllarmPinOn();

	bool IsDigitalSegnalPinOn();
	float GetSegnalValue();
	char* GetLastComunication();
	char* UID();
	
protected : 
	virtual bool IsDownValue();
	virtual float AnalogicRead();
	void SetLastComunication(char* lastComunication);
	uint8_t GetAnalogicSignalPin();
	

private :
	float _minValue;
	float _maxValue;
	int _analSignalPin;
	uint8_t _digitalSignalPin;
	int _alarmPin;
	float _sensorValue;
	char* _lastComunication;
	char* _uid;
};

