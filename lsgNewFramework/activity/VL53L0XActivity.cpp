#include "VL53L0XActivity.h"

#ifdef _DEBUG
#include <Arduino.h>
#endif


VL53L0XActivity::VL53L0XActivity(VL53L0XRepository& vl53L0XRepository, I2COstacleSensor** listOfi2COstacleSensor, uint8_t i2COstacleSensorsNumber){
	this->_listOfi2COstacleSensor = listOfi2COstacleSensor;
	this->_i2COstacleSensorsNumber = i2COstacleSensorsNumber;
	this->_vl53L0XRepository = &vl53L0XRepository;
}

bool VL53L0XActivity::isObstacleDetected(char* uid)
{

	for (int i = 0; i < this->_i2COstacleSensorsNumber; i++)
	{

		if (strcmp(this->_listOfi2COstacleSensor[i]->getUid(),uid) == 0)
		{
			if (this->_vl53L0XRepository->getMillimetersDistance() < 70)//this->_listOfi2COstacleSensor[i]->_minDistanceToObstacle)
			{
				this->_vl53L0XRepository->delaym(500);
				return true;
			}
		}
	}
	return false;

}

bool  VL53L0XActivity::isSensorOnError()
{
	_vl53L0XRepository->isSensorOnError();
}

uint16_t VL53L0XActivity::getDistance()
{
	return this->_vl53L0XRepository->getMillimetersDistance();
}
