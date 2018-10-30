
#include <arduino.h>
#include <pins_arduino.h>
#include "ActivityManager.h"



ActivityManager::ActivityManager(unsigned long seconds)
{
	_seconds = seconds * 1000;
	_millisToEnd = 0;
	_isFirstTime = true;
	this->accessMode = AccessMode::AccessAfterSetTime;
}

ActivityManager::~ActivityManager()
{
}

//void SoftwareClock::SetHours(unsigned int hours)
//{
//	_hours = hours;
//}

//void SoftwareClock::SetDelaySeconds(unsigned long seconds)
//{
//	_seconds = seconds * 1000;
//}
//void SoftwareClock::SetMinutes(unsigned intminutes)
//{
//}
//void SoftwareClock::SetMinutes(unsigned int minutes)
//{
//	_minutes = minutes;
//}
//unsigned int SoftwareClock::GetHours()
//{
//	//_hours = (uint8_t)(millis() / 3600000);
//	return _hours;
//}
//unsigned int SoftwareClock::GetSeconds()
//{
//	//_seconds = (uint8_t)(millis() / 1000);
//	return _seconds;
//}
//unsigned int SoftwareClock::GetMinutes()
//{
//	//_minutes = (uint8_t)(millis() / 60000);
//	return _minutes;
//}
//void SoftwareClock::Reset()
//{
//	_previousTime = 0;
//	_seconds = 0;
//	_minutes = 0;
//	_hours = 0;
//	_previousMillis = millis();
//
//}

//If method is called less then one second.
//void SoftwareClock::CountTime()
//{
//	if ((millis() - _previousMillis) >= (_previousTime))
//	{
//		_previousTime = _previousTime + 1000;  // use 100000 for uS
//		_seconds = _seconds + 1;
//		if (_seconds == 60)
//		{
//			_seconds = 0;
//			_minutes = _minutes + 1;
//		}
//		if (_minutes == 60)
//		{
//			_minutes = 0;
//			_hours = _hours + 1;
//		}
//		if (_hours == 13)
//		{
//			_hours = 1;
//		}
//		/*Serial.print(_hours);
//		Serial.print(":");
//		Serial.print(_minutes);
//		Serial.print(":");
//		Serial.println(_seconds);*/
//	}
//}

bool ActivityManager::IsDelayTimeFinished(bool isEnableFirstTime)
{
	if (this->accessMode == AccessMode::AlwaysAccess)
	{
		return true;
	}

	if (this->accessMode == AccessMode::NoAccess)
	{
		return false;
	}

	if (_isFirstTime == true && isEnableFirstTime == true)
	{
		_isFirstTime = false;
		return true;
	}

	if (this->accessMode == AccessMode::AccessAfterSetTime)
	{

		if (_millisToEnd == 0)
		{
			_millisToEnd = millis() + _seconds;
			return false;
		}
		else
		{
			if (millis() >= _millisToEnd)
			{
				_millisToEnd = 0;
				return true;
			}
			else
				return false;
		}

	}

	if (this->accessMode == AccessMode::NoAccesForSetTime)
	{
		if (_millisToEnd == 0)
		{
			_millisToEnd = millis() + _seconds;
			return false;
		}
		else
		{
			if (millis() >= _millisToEnd)
			{
				_millisToEnd = 0;
				this->accessMode = AccessMode::AlwaysAccess;
				return true;
			}
			else
				return false;
		}

	}

	 
}
