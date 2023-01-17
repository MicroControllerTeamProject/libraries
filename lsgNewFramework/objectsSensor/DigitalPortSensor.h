#pragma once
#include <stdint.h>
#include "..\model\DigitalPort.h"

class DigitalPortSensor //: public IDigitalPort
{
public:
	DigitalPortSensor(DigitalPort** irObstaclePOrts, uint8_t irObstaclePortsNumbers);
	 DigitalPort** getAllDigitalPorts();
	uint8_t getDigitalPortsNumber();
	 void setUid(char* uid);
	 char* getUid();
	 void enable(bool isEnable);
	 bool isEnable();
private:
	DigitalPort** _irObstaclePorts = nullptr;
	uint8_t _irObstaclePortsNumbers = 0;
	char* _uid;
	bool _isEnable = true;
};
