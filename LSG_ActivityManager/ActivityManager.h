#pragma once
class ActivityManager
{

private:
	//unsigned long _previousTime;
	//unsigned long _previousMillis;
	unsigned long _seconds;
	/*unsigned int _minutes;
	unsigned int _hours;*/

	unsigned long _millisToEnd;
	bool _isFirstTime;

	

public:
	ActivityManager(unsigned long seconds);
	~ActivityManager();
	bool IsDelayTimeFinished(bool isEnableFirstTime);
	bool _isEnable;
	
enum AccessMode
	{
		NoAccess,
		AlwaysAccess,
		AccessAfterSetTime,
		NoAccesForSetTime
	};
AccessMode accessMode;
};

