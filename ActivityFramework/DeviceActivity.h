#pragma once
//#include "DigitalPort.h"
#include "AnalogPort.h"
#include "DigitalPort.h"
#include "AvrMicroRepository.h"
#include "commonsLayer.h"
#include "DigitalPortSensor.h"
#include "AnalogPortSensor.h"


class DeviceActivity
{
public:
	/*DeviceActivity(AvrMicroRepository& avrMicroRepository, DigitalPortSensor** listOfdigitalPortSensors,uint8_t digitalPortSensorsNumber);*/
	//DeviceActivity(AvrMicroRepository& avrMicroRepository, AnalogPortSensor* listOfAnalogPortSensor,float _vref ,commonsLayer::analogRefMode mode, uint8_t analogPortSensorsNumber);
	
	DeviceActivity(AvrMicroRepository& avrMicroRepository, DigitalPortSensor digitalPortSensor);

	DeviceActivity(AvrMicroRepository& avrMicroRepository, AnalogPortSensor analogPortSensor, float _vref, commonsLayer::analogRefMode mode);
	
	DeviceActivity();

	void initializeDigitalPorts();
	float getVref();
	commonsLayer::analogRefMode vrefMode = commonsLayer::analogRefMode::DEFAULT_m;
	float _vref = 5;
	
	float getAnalogPortVrefVoltage(char* analogPortUid);
private:
	
protected:
	AvrMicroRepository* avrMicroRepository = nullptr;
	bool isDigitalPortOnAlarm();
	bool isAnalogPortOnAlarm(char* analogPortUid);
	DigitalPortSensor* _digitalPortSensor = nullptr;
	AnalogPortSensor* _analogPortSensor = nullptr;
};

