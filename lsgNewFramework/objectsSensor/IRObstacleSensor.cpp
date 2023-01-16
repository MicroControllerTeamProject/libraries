#include "IRObstacleSensor.h"

#ifdef _DEBUG
#include <Arduino.h>
#endif

IRObstacleSensor::IRObstacleSensor(DigitalPort** irObstaclePorts,uint8_t irObstaclePortsNumbers)
{
	this->_irObstaclePorts = irObstaclePorts;
	this->_irObstaclePortsNumbers = irObstaclePortsNumbers;
}

DigitalPort** IRObstacleSensor::getAllDigitalPorts()
{
	return this->_irObstaclePorts;
}

uint8_t IRObstacleSensor::getDigitalPortsNumber()
{
	return this->_irObstaclePortsNumbers;
}

void IRObstacleSensor::setUid(char* uid)
{
	this->_uid = uid;
}

char* IRObstacleSensor::getUid()
{
	return this->_uid;
}

void IRObstacleSensor::enable(bool isEnable)
{
}

bool IRObstacleSensor::isEnable()
{
	return false;
}
