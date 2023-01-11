#include "IRObstacleSensorActivity.h"
#include <stdlib.h>
#include <string.h>

IRObstacleSensorActivity::IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** obstaclePort,uint8_t portNumbers)  : DeviceActivity(avrMicroRepository,obstaclePort,portNumbers){
}

bool IRObstacleSensorActivity::isObstacleDetected(char* uid)
{
	return this->isDigitalPortOnAlarm(uid);
}

bool IRObstacleSensorActivity::isSensorOnError()
{
	return false;
}

