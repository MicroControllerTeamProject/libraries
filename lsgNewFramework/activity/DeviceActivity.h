#pragma once
//#include "DigitalPort.h"
#include "..\model\AnalogPort.h"
#include "..\model\DigitalPort.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\commons\commonsLayer.h"
#include "..\objectsSensor\DigitalPortSensor.h"
#include "..\objectsSensor\AnalogPortSensor.h"


class DeviceActivity
{
public:
	DeviceActivity(AvrMicroRepository& avrMicroRepository, DigitalPortSensor** digitalPortSensors,uint8_t digitalPortSensorsNumber);
	/*DeviceActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** digitalPort);*/
	DeviceActivity(AvrMicroRepository& avrMicroRepository, AnalogPortSensor** analogPortSensor,float _vref ,commonsLayer::analogRefMode mode, uint8_t analogPortSensorsNumber);
	DeviceActivity();
	//virtual bool isThereAnyPortOnAlarm();
	//virtual String getLastAlarmDescription();
	//bool digitalWriteByName(String portName, uint8_t pinLevel);
	//uint8_t digitalReadByName(String portName);
	/*float analogReadVoltageByName(String portName);
	int analogReadByName(String portName);*/

	//const char* getDeviceOnErrorUID();
	void initializeDigitalPorts();
	/*AnalogPort** getAllAnalogPorts();*/
	//DigitalPort** getAllDigitalPorts();
	
	
	/*DigitalPort** digitalPort;*/
	/*AnalogPort** analogPort;*/
	
	/*uint8_t _analogPortsNumber = 0;*/
	char _lastAlarmDescription[10];
	/*String lastAlarmDescription = "";
	String lastErrorDescription = "";*/
	char _lastAlarmCode;
	char _lastErrorCode;

	//virtual float getUnitOfMisureValue(String portName);
	//virtual  float  getCustomMisureValue();
	//bool isThereAnyCustomMisureOnAlarm();
	//bool isThereAnyDigitalPortOnAlarm();
	/*float analogReadVoltageByPin(uint8_t pin);*/
	float getVref();
	commonsLayer::analogRefMode vrefMode = commonsLayer::analogRefMode::DEFAULT_m;
	/*char getLastErrorCode();
	void setLastErrorCode(char errorCode);*/
	/*const char* deviceOnErrorUID = {};
	char* deviceErrorValue = {};*/

	float _vref = 5;
	AvrMicroRepository* avrMicroRepository = nullptr;
	float getAnalogPortVrefVoltage(char* portName);
private:
	
protected:
	/*bool isThereAnyAnalogPortOnAlarm();*/
	bool isDigitalPortOnAlarm(char* portName);
	bool isAnalogPortOnAlarm(char* portName);
	DigitalPortSensor** digitalPortSensors;
	AnalogPortSensor** analogPortSensors;
	uint8_t _analogPortsSensorNumber = 0;
	uint8_t _digitalPortsNumber = 0;
	uint8_t _digitalPortSensorNumber = 0;
};

