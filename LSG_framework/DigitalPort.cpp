#pragma once

#include "DigitalPort.h"
#include "stdint.h"

DigitalPort::DigitalPort(String uid, uint8_t pin,uint8_t mode)
{
	this->_uid = uid;
	this->_pin = pin;
}

String DigitalPort::getUid()
{
	return _uid;
}

uint8_t DigitalPort::getPin()
{
	return _pin;
}


