#include "ISensor.h"
bool ISensor::IsSensorWorking(){}

bool ISensor::SetIsSentSMSAllarm(bool isDetectedAllarm)
{
	_isDetectedAllarm = isDetectedAllarm;
}

bool ISensor::IsSentSMSAllarm()
{
	return _isDetectedAllarm;
}