#include "AnalogPort.h"

AnalogPort::AnalogPort(const char uid[6], const uint8_t pin) {
	_uid = uid;
	_pin = pin;
}

const char* AnalogPort::getUid(){
	return _uid;
}

uint8_t AnalogPort::getPin(){
	return _pin;
}