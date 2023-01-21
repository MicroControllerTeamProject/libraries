#include "I2COstacleSensor.h"


I2COstacleSensor::I2COstacleSensor(char* uid,uint8_t address, uint16_t minDistanceToObstacle, uint16_t maxDistanceToObstacle) {
	this->_address = address;
	this->_minDistanceToObstacle = minDistanceToObstacle;
	this->_uid = uid;
}

char* I2COstacleSensor::getUid()
{
	return this->_uid;
}

uint16_t I2COstacleSensor::getAddress()
{
	return this->_address;
}

void I2COstacleSensor::enable(bool isEnable)
{
}

bool I2COstacleSensor::isEnable()
{
	return false;
}


