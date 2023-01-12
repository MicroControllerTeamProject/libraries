#pragma once
//#include "DigitalPort.h"
#include "..\model\AnalogPort.h"
#include "..\model\DigitalPort.h"
#include "..\interfaces\IDigitalPorts.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\commons\commonsLayer.h"


class DeviceActivity
{
public:
	DeviceActivity(AvrMicroRepository& avrMicroRepository, IDigitalPorts* digitalPortSensor);
	DeviceActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** digitalPort);
	DeviceActivity(AvrMicroRepository& avrMicroRepository, AnalogPort** analogPort,float _vref ,commonsLayer::analogRefMode mode, uint8_t analogPortsNumber);
	DeviceActivity();
	//virtual bool isThereAnyPortOnAlarm();
	//virtual String getLastAlarmDescription();
	//bool digitalWriteByName(String portName, uint8_t pinLevel);
	//uint8_t digitalReadByName(String portName);
	/*float analogReadVoltageByName(String portName);
	int analogReadByName(String portName);*/

	//const char* getDeviceOnErrorUID();
	AnalogPort** getAllAnalogPorts();
	DigitalPort** getAllDigitalPorts();
	uint8_t getAnalogPortsNumber();
	uint8_t getDigitalPortsNumber();
	
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
	/*char lastErrorCode = 'X';*/
	/*uint8_t deviceErrorPin = {};*/
	float _vref = 5;
	AvrMicroRepository* avrMicroRepository = nullptr;
private:
	
protected:
	
	bool isThereAnyAnalogPortOnAlarm();
	bool isDigitalPortOnAlarm(char* portName);
	bool isDigitalPortOnAlarm(uint8_t pinNumber);
	bool isThereAnyDigitalPortOnAlarm();
	AnalogPort** analogPort;
	DigitalPort** digitalPort;
	uint8_t _analogPortsNumber = 0;
	uint8_t digitalPortsNumber = 0;
};

