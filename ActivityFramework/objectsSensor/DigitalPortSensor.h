#pragma once
#include <stdint.h>
#include "../model/DigitalPort.h"

class DigitalPortSensor //: public IDigitalPort
{
public:
	DigitalPortSensor(char* uid,DigitalPort* listOfDigitalPorts, uint8_t digitalPortsNumbers);
	DigitalPortSensor();
	 DigitalPort* getAllDigitalPorts();
	uint8_t getDigitalPortsNumber();
	 void setUid(char* uid);
	 char* getUid();
	 void enable(bool isEnable);
	 bool isEnable();
private:
	DigitalPort* _listOfDigitalPorts = nullptr;
	uint8_t _digitalPortsNumbers = 0;
	char* _uid;
	bool _isEnable = true;
};
