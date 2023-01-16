#include "IRObstacleSensorActivity.h"
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
#include <Arduino.h>
#endif

IRObstacleSensorActivity::IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** obstaclePort)  : DeviceActivity(avrMicroRepository,obstaclePort){
}

IRObstacleSensorActivity::IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, IDigitalPorts** obstacleDigitalSensor,uint8_t obstacleDigitalSensorsNumber) : DeviceActivity(avrMicroRepository, obstacleDigitalSensor, obstacleDigitalSensorsNumber){
}

bool IRObstacleSensorActivity::isObstacleDetected(char* uid){
	return this->isDigitalPortOnAlarm(uid);
}

bool IRObstacleSensorActivity::isSensorOnError(){
	return false;
}

