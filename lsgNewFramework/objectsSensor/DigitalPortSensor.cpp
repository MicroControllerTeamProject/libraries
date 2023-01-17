#include "DigitalPortSensor.h"

#ifdef _DEBUG
#include <Arduino.h>
#endif

DigitalPortSensor::DigitalPortSensor(DigitalPort** irObstaclePorts,uint8_t irObstaclePortsNumbers)
{
	this->_irObstaclePorts = irObstaclePorts;
	this->_irObstaclePortsNumbers = irObstaclePortsNumbers;
}

DigitalPort** DigitalPortSensor::getAllDigitalPorts()
{
	return this->_irObstaclePorts;
}

uint8_t DigitalPortSensor::getDigitalPortsNumber()
{
	return this->_irObstaclePortsNumbers;
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
