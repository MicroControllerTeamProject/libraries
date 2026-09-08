#include "ISensor.h"
bool ISensor::IsSensorWorking(){ return false; }

bool ISensor::SetIsSentSMSAllarm(bool isDetectedAllarm)
{
	_isDetectedAllarm = isDetectedAllarm;
	return _isDetectedAllarm;
}

bool ISensor::IsSentSMSAllarm()
{
	return _isDetectedAllarm;
}