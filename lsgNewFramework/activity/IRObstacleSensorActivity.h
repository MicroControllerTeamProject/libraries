#pragma once
#include "DeviceActivity.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\model\DigitalPort.h"
#include "..\commons\commonsLayer.h"
#include "..\interfaces\IntrefaceObstacleSensor.h"

class IRObstacleSensorActivity : public DeviceActivity,public IntrefaceObstacleSensor
{
public:
	IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** obstaclePort, uint8_t portNumbers);
	//bool isAnObstacleDetected();
	//bool isObstacleDetected(char* portName);
	AvrMicroRepository* avrMicroRepository = nullptr;
private:
};

