#pragma once
#include "DeviceActivity.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\model\DigitalPort.h"
#include "..\commons\commonsLayer.h"
#include "..\interfaces\InterfaceObstacleActivity.h"

class IRObstacleSensorActivity : public DeviceActivity,public InterfaceObstacleActivity
{
public:
	IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** obstaclePort, uint8_t portNumbers);
	AvrMicroRepository* avrMicroRepository = nullptr;
	virtual bool isObstacleDetected(char* uid);
	virtual bool isSensorOnError();
private:
};

