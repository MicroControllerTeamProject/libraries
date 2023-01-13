#include "IRObstacleSensorActivity.h"
#include <stdlib.h>
#include <string.h>

IRObstacleSensorActivity::IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** obstaclePort)  : DeviceActivity(avrMicroRepository,obstaclePort){
}

IRObstacleSensorActivity::IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, IDigitalPorts** obstacleDigitalSensor) : DeviceActivity(avrMicroRepository, obstacleDigitalSensor){
}

bool IRObstacleSensorActivity::isObstacleDetected(char* uid)
{
	return this->isDigitalPortOnAlarm(uid);
}

bool IRObstacleSensorActivity::isSensorOnError()
{
	return false;
}

