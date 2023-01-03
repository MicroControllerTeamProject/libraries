#pragma once
#include "DeviceActivity.h"
#include <stdint.h>
#include <string.h>

class SimModuleActivity : public DeviceActivity
{
public:
	SimModuleActivity(DigitalPort** ports, uint8_t portsNumber);
	SimModuleActivity();
	bool makeCall(AvrMicroRepository& avrMicroRepository);
	/*void makeCall(AvrMicroRepository& avrMicroRepository);*/
	void setPrefixAndphoneNumber(char* _prefixAndphoneNumber);
	void setBaud(long unsigned _baud);
private:
	char* _prefixAndphoneNumber;
	long unsigned _baud;
};

