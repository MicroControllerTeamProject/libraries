#pragma once
#include "DeviceActivity.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\model\DigitalPort.h"
#include "..\commons\commonsLayer.h"
#include "..\interfaces\InterfaceObstacleActivity.h"
#include "..\interfaces\IDigitalPorts.h"
#include "..\objectsSensor\IRObstacleSensor.h"

class IRObstacleSensorActivity : public DeviceActivity,public InterfaceObstacleActivity
{
public:
	IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** obstaclePort);
	IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, IDigitalPorts** obstacleDigitalSensor);
	AvrMicroRepository* avrMicroRepository = nullptr;
	virtual bool isObstacleDetected(char* uid);
	virtual bool isSensorOnError();
private:
};

