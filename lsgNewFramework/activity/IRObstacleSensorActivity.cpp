#include "IRObstacleSensorActivity.h"
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
#include <Arduino.h>
#endif

IRObstacleSensorActivity::IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, IDigitalPort** obstacleDigitalSensor,uint8_t obstacleDigitalSensorsNumber) : DeviceActivity(avrMicroRepository, obstacleDigitalSensor, obstacleDigitalSensorsNumber){
}

bool IRObstacleSensorActivity::isObstacleDetected(char* uid){
	this->avrMicroRepository->delaym(500);
	return this->isDigitalPortOnAlarm(uid);
}

bool IRObstacleSensorActivity::isSensorOnError(){
	return false;
}

uint16_t IRObstacleSensorActivity::getDistance()
{
	return 0;
}

