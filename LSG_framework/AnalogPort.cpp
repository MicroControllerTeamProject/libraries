#include "AnalogPort.h"

AnalogPort::AnalogPort(String uid, uint8_t pin)
{
	_uid = uid;
	_pin = pin;
}

String AnalogPort::getUid()
{
	return _uid;
}

uint8_t AnalogPort::getPin()
{
	return _pin;
}