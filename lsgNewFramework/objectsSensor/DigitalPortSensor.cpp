#include "DigitalPortSensor.h"

#ifdef _DEBUG
#include <Arduino.h>
#endif

DigitalPortSensor::DigitalPortSensor(DigitalPort** listOfDigitalPorts,uint8_t digitalPortsNumbers)
{
	this->_listOfDigitalPorts = listOfDigitalPorts;
	this->_digitalPortsNumbers = digitalPortsNumbers;
}

DigitalPort** DigitalPortSensor::getAllDigitalPorts()
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
}

bool DigitalPortSensor::isEnable()
{
	return false;
}
