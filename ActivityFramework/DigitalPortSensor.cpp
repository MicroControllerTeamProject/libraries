#include "DigitalPortSensor.h"

#ifdef _DEBUG
#include <Arduino.h>
#endif

DigitalPortSensor::DigitalPortSensor(char* uid,DigitalPort* listOfDigitalPorts,uint8_t digitalPortsNumbers)
{
	this->_listOfDigitalPorts = listOfDigitalPorts;
	this->_digitalPortsNumbers = digitalPortsNumbers;
	this->_uid = uid;
}

DigitalPortSensor::DigitalPortSensor()
{
}

DigitalPort* DigitalPortSensor::getAllDigitalPorts()
{
	return this->_listOfDigitalPorts;
}

uint8_t DigitalPortSensor::getDigitalPortsNumber()
{
	return this->_digitalPortsNumbers;
}

void DigitalPortSensor::setUid(char* uid)
{
	this->_uid = uid;
}

char* DigitalPortSensor::getUid()
{
	return this->_uid;
}

void DigitalPortSensor::enable(bool isEnable)
{
	this->_isEnable = isEnable;
}

bool DigitalPortSensor::isEnable()
{
	return this->_isEnable;
}
