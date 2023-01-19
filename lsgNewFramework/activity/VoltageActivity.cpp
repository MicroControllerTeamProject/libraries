#include "VoltageActivity.h"
#include "..\repository\AvrMicroRepository.h"

VoltageActivity::VoltageActivity(AvrMicroRepository& avrMicroRepository,AnalogPortSensor** _listOfAnalogPortSensor, float vref, commonsLayer::analogRefMode mode, uint8_t analogPortSensorsNumber) : DeviceActivity(avrMicroRepository, _listOfAnalogPortSensor, vref,mode, analogPortSensorsNumber) {
}

bool VoltageActivity::isVoltageOutOfRange(char* portName) {
	if (!(this->isAnalogPortOnAlarm(portName))) return false;
	return true;
}

float  VoltageActivity::getVoltage(char* portName)
{
	return this->getAnalogPortVrefVoltage(portName);
}

char* VoltageActivity::getLipoBatteryGrafBarLevel(char* portName)
{
			float batteryVoltageLevel = this->getAnalogPortVrefVoltage(portName);
			if (batteryVoltageLevel <= 3.25f)
				return "[    ]o";
			if (batteryVoltageLevel <= 3.30f)
				return "[|   ]o";
			if (batteryVoltageLevel <= 3.40f)
				return "[||  ]o";
			if (batteryVoltageLevel <= 3.60f)
				return "[||| ]o";
			if (batteryVoltageLevel <= 5.50f)
				return "[||||]o";

	return "";
}