#include "AnalogPortSensor.h"

#ifdef _DEBUG
#include <Arduino.h>
#endif

AnalogPortSensor::AnalogPortSensor(AnalogPort** listOfAnalogPorts, uint8_t analogPortsNumbers)
{
	this->_listOfAnalogPorts = listOfAnalogPorts;
	this->_analogPortsNumbers = analogPortsNumbers;
}

AnalogPort** AnalogPortSensor::getAllAnalogPorts()
{
	return this->_listOfAnalogPorts;
}

uint8_t AnalogPortSensor::getAnalogPortsNumber()
{
	return this->_analogPortsNumbers;
}

void AnalogPortSensor::setUid(char* uid)
{
	this->_uid = uid;
}

char* AnalogPortSensor::getUid()
{
	return this->_uid;
}

void AnalogPortSensor::enable(bool isEnable)
{
}

bool AnalogPortSensor::isEnable()
{
	return false;
}
