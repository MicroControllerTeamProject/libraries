#pragma once
#include "..\model\DigitalPort.h"

class IDigitalPort
{
public:
	virtual ~IDigitalPort() {}
	virtual DigitalPort** getAllDigitalPorts() = 0;
	virtual uint8_t getDigitalPortsNumber() = 0;
	virtual void setUid(char* uid) = 0;
	virtual char* getUid()=0;
	virtual void enable(bool isEnable)=0;
	virtual bool isEnable()=0;
};