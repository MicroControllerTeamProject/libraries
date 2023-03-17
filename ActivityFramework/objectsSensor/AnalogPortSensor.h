#pragma once
#include <stdint.h>
#include "../model/AnalogPort.h"

class AnalogPortSensor
{
public:
	AnalogPortSensor(char* uid,AnalogPort* listOfAnalogPorts, uint8_t analogPortsNumbers);
	AnalogPortSensor();
	AnalogPort* getAllAnalogPorts();
	uint8_t getAnalogPortsNumber();
	void setUid(char* uid);
	char* getUid();
	void enable(bool isEnable);
	bool isEnable();
private:
	AnalogPort* _listOfAnalogPorts = nullptr;
	uint8_t _analogPortsNumbers = 0;
	char* _uid;
	bool _isEnable = true;
};
