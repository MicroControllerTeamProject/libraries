#include "I2COstacleSensor.h"


I2COstacleSensor::I2COstacleSensor(uint8_t address,char* uid){
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


