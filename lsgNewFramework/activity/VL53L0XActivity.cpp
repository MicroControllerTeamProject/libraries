#include "VL53L0XActivity.h"

#ifdef _DEBUG
#include <Arduino.h>
#endif


VL53L0XActivity::VL53L0XActivity(VL53L0XRepository& vl53L0XRepository, I2COstacleSensor** listOfi2COstacleSensor, uint8_t i2COstacleSensorsNumber){
	this->_listOfi2COstacleSensor = listOfi2COstacleSensor;
	this->_i2COstacleSensorsNumber = i2COstacleSensorsNumber;
	this->_vl53L0XRepository = &vl53L0XRepository;

	for (int i = 0; i < this->_i2COstacleSensorsNumber; i++)
	{
		this->_vl53L0XRepository->initContinuos(this->_listOfi2COstacleSensor[i]->getAddress());
	}
}
bool VL53L0XActivity::isObstacleDetected(char* uid)
{
	//uint8_t deviceAddress = atoi(uid);
	for (int i = 0; i < this->_i2COstacleSensorsNumber; i++)
	{
		if (strcmp(this->_listOfi2COstacleSensor[i]->getUid(), uid) == 0)
		{
			this->_vl53L0XRepository->setAddress(this->_listOfi2COstacleSensor[i]->getAddress());
			
			if (this->_vl53L0XRepository->getMillimetersDistance() < _listOfi2COstacleSensor[i]->_minDistanceToObstacle)
			{
				while (this->_vl53L0XRepository->getMillimetersDistance() < _listOfi2COstacleSensor[i]->_minDistanceToObstacle){

				}

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
