#pragma once
#include "DeviceActivity.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\model\DigitalPort.h"
#include "..\commons\commonsLayer.h"
#include "..\interfaces\InterfaceObstacleActivity.h"

class IRObstacleSensorActivity : public DeviceActivity,public InterfaceObstacleActivity
{
public:
	IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** obstaclePort);
	AvrMicroRepository* avrMicroRepository = nullptr;
	virtual bool isObstacleDetected(char* uid);
	virtual bool isSensorOnError();
private:
};

