#include "VoltageActivity.h"
#include "..\repository\AvrMicroRepository.h"

VoltageActivity::VoltageActivity(AvrMicroRepository& avrMicroRepository,AnalogPortSensor** _listOfAnalogPortSensor, float vref, commonsLayer::analogRefMode mode, uint8_t analogPortSensorsNumber) 
	: DeviceActivity(avrMicroRepository, _listOfAnalogPortSensor, vref,mode, analogPortSensorsNumber) {
}

bool VoltageActivity::isVoltageOutOfRange(char* portName) {
	if (!(this->isAnalogPortOnAlarm(portName))) return false;
	return true;
}

float  VoltageActivity::getVoltage(char* portName)
{
	return this->getAnalogPortVrefVoltage(portName);
}

char* VoltageActivity::getGrafBarLevel(char* portName,float minValue,float maxValue)
{
			uint8_t numbersOfLevels = 7;
			float deltaValue = (maxValue - minValue) / (float)(numbersOfLevels - 2);
			float batteryVoltageLevel = this->getAnalogPortVrefVoltage(portName);
			if (batteryVoltageLevel <= minValue)
				return "[      ]o";
			if (batteryVoltageLevel <= minValue + deltaValue)
				return "[|     ]o";
			if (batteryVoltageLevel <= minValue + (deltaValue * 2))
				return "[||    ]o";
			if (batteryVoltageLevel <= minValue + (deltaValue * 3))
				return "[|||   ]o";
			if (batteryVoltageLevel <= minValue + (deltaValue * 4))
				return "[||||  ]o";
			if (batteryVoltageLevel <= minValue + (deltaValue * 5))
				return "[||||| ]o";
			if (batteryVoltageLevel <= maxValue)
				return "[||||||]o";
	return "";
}