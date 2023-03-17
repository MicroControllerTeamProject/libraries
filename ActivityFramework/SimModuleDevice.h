#pragma once
#include "DigitalPortSensor.h"

class SimModuleDevice : public DigitalPortSensor
{
public:
	SimModuleDevice(char* uid, DigitalPort* listOfDigitalPorts, uint8_t digitalPortsNumbers);
	SimModuleDevice();
	void init(char* prefixNumber, char* phoneNumber);

	void setEnableSmsStatus(bool isSmsDisabled);
	bool getEnableSmsStatus();

	void setEnableCallStatus(bool isCallDisabled);
	bool getEnableCallStatus();

	void setEnableDeviceStatus(bool isDeviceDisabled);
	bool getEnableDeviceStatus();

	void setBlockedStrangerCaller(bool isDeviceDisabled);
	bool getBlockedStrangerCaller();


	char* getPhoneNumber();
	char* getPrefixNumber();
	/*unsigned long getBaud();*/
	uint8_t _rx;
	uint8_t _tx;
private:
	bool _isBlockedStrangerCaller = true;
	bool _isSmsDisabled = false;
	bool _isCallDisable = false;
	bool isTurnedOff = false;
	bool isInSleepMode = false;
	char* _phoneNumber = {};
	char* _prefixNumber = {};
	/*unsigned long _baud = 0;*/
};

