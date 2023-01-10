#include "IRObstacleSensorActivity.h"
#include <stdlib.h>
#include <string.h>

AvrMicroRepository* _avrMicroRepository = nullptr;
DigitalPort** _obstaclePort = nullptr;
uint8_t _portNumbers = 0;

IRObstacleSensorActivity::IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** obstaclePort,uint8_t portNumbers)  : DeviceActivity(avrMicroRepository,obstaclePort,portNumbers)
{
	_avrMicroRepository = &avrMicroRepository;
	_obstaclePort = obstaclePort;
	_portNumbers = portNumbers;
}

//bool IRObstacleSensorActivity::isObstacleDetected(char* portName)
//{
//	return this->isDigitalPortOnAlarm(portName);
//}
//
//bool IRObstacleSensorActivity::isAnObstacleDetected()
//{
//	return false;//this->isThereAnyDigitalPortOnAlarm();
//}


bool IntrefaceObstacleSensor::isObstacleDetected(char* uid)
{
	for (int i = 0; i < _portNumbers; i++)
	{
		_obstaclePort[i]->isOnError = false;
		if (_obstaclePort[i]->isEnable && (_obstaclePort[i]->direction == DigitalPort::input))
		{
			if ((strcmp(uid, _obstaclePort[i]->getUid()) == 0) && _obstaclePort[i]->alarmTriggerOn == DigitalPort::AlarmOn::low && _avrMicroRepository->digitalReadm(_obstaclePort[i]->getPin()) == 0/*LOW*/)
			{
				return true;
			}
			if ((strcmp(uid, _obstaclePort[i]->getUid()) == 0) && _obstaclePort[i]->alarmTriggerOn == DigitalPort::AlarmOn::high && _avrMicroRepository->digitalReadm(_obstaclePort[i]->getPin()) == 1/*HIGH*/)
			{
				return true;
			}
		}
	}
	return false;
}

