#include "AnalogPort.h"

AnalogPort::AnalogPort(char* uid, const uint8_t pin) {
	this->_uid = uid;
	this->_pin = pin;
}

AnalogPort::AnalogPort(){
}

char* AnalogPort::getUid(){
	return this->_uid;
}

uint8_t AnalogPort::getPin(){
	return this->_pin;
}