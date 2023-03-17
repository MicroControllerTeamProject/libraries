#include "VoltageActivity.h"
#include "../repository/AvrMicroRepository.h"

VoltageActivity::VoltageActivity(AvrMicroRepository& avrMicroRepository,AnalogPortSensor& analogPortSensor, float vref, commonsLayer::analogRefMode mode) 
	: DeviceActivity(avrMicroRepository, analogPortSensor, vref,mode) {
}

VoltageActivity::VoltageActivity()
{
}

bool VoltageActivity::isVoltageOutOfRange(char* analogPortUid) {
	if (!(this->isAnalogPortOnAlarm(analogPortUid))) return false;
	return true;
}

float  VoltageActivity::getVoltage(char* sensorUid)
{
	return this->getAnalogPortVrefVoltage(sensorUid);
}

char* VoltageActivity::getGrafBarLevel(char* sensorUid,float minValue,float maxValue,float chargeVoltageValue)
{
			uint8_t numbersOfLevels = 6;
			float deltaValue = 0;
			float batteryVoltageLevel = this->getAnalogPortVrefVoltage(sensorUid);
			if (batteryVoltageLevel > maxValue)
			{
				maxValue = chargeVoltageValue;
			}
			deltaValue = (maxValue - minValue) / (float)(numbersOfLevels);
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
			if (batteryVoltageLevel <= maxValue + deltaValue)
				return "[||||||]o";
	return "[OVER-V]o";
}