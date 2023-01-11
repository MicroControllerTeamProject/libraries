#include "VL53L0XActivity.h"

VL53L0XRepository* _vl53L0XRepository = nullptr;
VL53L0XActivity::VL53L0XActivity(VL53L0XRepository & vl53L0XRepository){
}

bool InterfaceObstacleSensor::isObstacleDetected(char* uid)
{
	return false;
}

bool  InterfaceObstacleSensor::isSensorOnError()
{
	_vl53L0XRepository->isSensorOnError();
}
