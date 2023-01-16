#include "VL53L0XActivity.h"


VL53L0XActivity::VL53L0XActivity(VL53L0XRepository &vl53L0XRepository){
}

bool VL53L0XActivity::isObstacleDetected(char* uid)
{
	return false;
}

bool  VL53L0XActivity::isSensorOnError()
{
	_vl53L0XRepository->isSensorOnError();
}

uint16_t VL53L0XActivity::getDistance()
{
	return 0;
}
