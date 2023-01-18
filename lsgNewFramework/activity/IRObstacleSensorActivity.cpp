#include "IRObstacleSensorActivity.h"
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
#include <Arduino.h>
#endif

IRObstacleSensorActivity::IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPortSensor** obstacleDigitalSensor,uint8_t obstacleDigitalSensorsNumber) : DeviceActivity(avrMicroRepository, obstacleDigitalSensor, obstacleDigitalSensorsNumber){
}

bool IRObstacleSensorActivity::isObstacleDetected(char* uid){
	
	bool returnValue =  this->isDigitalPortOnAlarm(uid);
	this->avrMicroRepository->delaym(100);
	if (this->isDigitalPortOnAlarm(uid) && returnValue) return false;
	return returnValue;
}

bool IRObstacleSensorActivity::isSensorOnError(){
	return false;
}

uint16_t IRObstacleSensorActivity::getDistance()
{
	return 0;
}

