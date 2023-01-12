#include "IRObstacleSensor.h"

IRObstacleSensor::IRObstacleSensor(DigitalPort** irObstaclePOrts)
{
	this->_irObstaclePOrts = irObstaclePOrts;
}

DigitalPort** IRObstacleSensor::getAllDigitalPorts()
{
	return this->_irObstaclePOrts;
}

void IRObstacleSensor::setUid(char* uid)
{

}

char* IRObstacleSensor::getUid()
{
	return nullptr;
}

void IRObstacleSensor::enable(bool isEnable)
{
}

bool IRObstacleSensor::isEnable()
{
	return false;
}
