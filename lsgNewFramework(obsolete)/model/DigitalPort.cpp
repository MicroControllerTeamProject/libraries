#pragma once

#include "DigitalPort.h"

DigitalPort::DigitalPort(char* uid, uint8_t pin)
{
	this->_uid = uid;
	this->_pin = pin;
}

char* DigitalPort::getUid()
{
	return _uid;
}

uint8_t DigitalPort::getPin()
{
	return _pin;
}


