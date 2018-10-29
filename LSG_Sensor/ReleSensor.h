#pragma once
#include "AnalogicSensor.h"
#include "IRele.h"

class ReleSensor : public AnalogicSensor , public IRele 
{
private:
	bool _isReleClose;
	bool _isCloseOnHigh;
	uint8_t _signalPin;
public:
	ReleSensor(char* uid, uint8_t signalPin, bool isCloseOnHigh);
	~ReleSensor();
	bool IsSensorWorking();
	void Close();
	void Open();
	bool IsClose();

};

