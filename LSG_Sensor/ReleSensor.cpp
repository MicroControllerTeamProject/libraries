#include "ReleSensor.h"
#include <arduino.h>
#include <pins_arduino.h> 


ReleSensor::ReleSensor(char* uid,uint8_t signalPin,bool isCloseOnHIGH) : AnalogicSensor(uid)
{
	pinMode(signalPin, OUTPUT);
	_signalPin = signalPin; 
	SetIsSentSMSAllarm(false);
	_isCloseOnHigh = isCloseOnHIGH;
}


ReleSensor::~ReleSensor()
{
}

bool ReleSensor::IsSensorWorking()
{
	//TODO Verificare se possibile condizionare pin on segnale e corrente bassa.
	SetLastComunication("is working");
	return true;
}

void ReleSensor::Close()
{
	if (_isCloseOnHigh)
		digitalWrite(_signalPin,HIGH);
	else
		digitalWrite(_signalPin, LOW);
	_isReleClose = true;
}

void ReleSensor::Open()
{
	if (_isCloseOnHigh)
		digitalWrite(_signalPin, LOW);
	else
		digitalWrite(_signalPin, HIGH);
	_isReleClose = false;
}

bool ReleSensor::IsClose()
{
	return _isReleClose;
}



