#include "IRObstacleSensorActivity.h"

IRObstacleSensorActivity::IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** obstaclePort,uint8_t portNumbers)  : DeviceActivity(avrMicroRepository,obstaclePort,portNumbers)
{

}

bool IRObstacleSensorActivity::isObstacleDetected()
{
	return this->isThereAnyDigitalPortOnAlarm();
}

