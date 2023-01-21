#include "IRObstacleSensorActivity.h"
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
#include <Arduino.h>
#endif

IRObstacleSensorActivity::IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPortSensor** obstacleDigitalSensor,uint8_t obstacleDigitalSensorsNumber) : DeviceActivity(avrMicroRepository, obstacleDigitalSensor, obstacleDigitalSensorsNumber){
}

bool IRObstacleSensorActivity::isObstacleDetected(char* sensorUid){
	
	bool returnValue =  this->isDigitalPortOnAlarm(sensorUid);
	//this->avrMicroRepository->delaym(100);
	while (this->isDigitalPortOnAlarm(sensorUid) && returnValue) { this->avrMicroRepository->delaym(50); }
	//if (this->isDigitalPortOnAlarm(sensorUid) && returnValue) return false;
	return returnValue;
}

bool IRObstacleSensorActivity::isSensorOnError(){
	return false;
}

uint16_t IRObstacleSensorActivity::getDistance()
{
	return 0;
}

