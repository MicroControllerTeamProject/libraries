#pragma once
#include "..\interfaces\IDigitalPorts.h"

class IRObstacleSensor : public IDigitalPort
{
public:
	IRObstacleSensor(DigitalPort** irObstaclePOrts, uint8_t irObstaclePortsNumbers);
	virtual DigitalPort** getAllDigitalPorts();
	virtual uint8_t getDigitalPortsNumber();
	virtual void setUid(char* uid);
	virtual char* getUid();
	virtual void enable(bool isEnable);
	virtual bool isEnable();
private:
	DigitalPort** _irObstaclePorts = nullptr;
	uint8_t _irObstaclePortsNumbers = 0;
	char* _uid;
	bool _isEnable = true;
};
