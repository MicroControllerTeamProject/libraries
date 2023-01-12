#pragma once
#include "..\interfaces\IDigitalPorts.h"

class IRObstacleSensor : public IDigitalPorts
{
public:
	IRObstacleSensor(DigitalPort** irObstaclePOrts);
	virtual DigitalPort** getAllDigitalPorts();
	virtual void setUid(char* uid);
	virtual char* getUid();
	virtual void enable(bool isEnable);
	virtual bool isEnable();
private:
	DigitalPort** _irObstaclePOrts = nullptr;
	char* _uid;
	bool _isEnable = true;
};
