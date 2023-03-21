#include "AnalogPort.h"

AnalogPort::AnalogPort(const char uid[6], const uint8_t pin) {
	this->_uid = uid;
	this->_pin = pin;
}

AnalogPort::AnalogPort(){
}

const char* AnalogPort::getUid(){
	return this->_uid;
}

uint8_t AnalogPort::getPin(){
	return this->_pin;
}