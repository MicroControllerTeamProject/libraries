#pragma once
#include "DeviceActivity.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\model\DigitalPort.h"
#include "..\commons\commonsLayer.h"

class IRObstacleSensorActivity : public DeviceActivity
{
public:
	IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** obstaclePort, uint8_t portNumbers);
	bool isObstacleDetected();
private:
};

