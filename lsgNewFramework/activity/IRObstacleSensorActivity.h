#pragma once
#include "DeviceActivity.h"


class IRObstacleSensorActivity : public DeviceActivity
{
public:
	IRObstacleSensorActivity(AvrMicroRepository* avrMicroRepository, DigitalPort** obstaclePort, uint8_t portNumbers);
	bool isObstacleDetected();
private:
	AvrMicroRepository& _avrMicroRepository;
};

