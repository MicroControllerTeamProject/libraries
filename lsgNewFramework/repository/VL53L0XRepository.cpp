#include "VL53L0XRepository.h"
#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X vl53L0X;
VL53L0XRepository::VL53L0XRepository() {
	Wire.begin();
}
void VL53L0XRepository::init(uint8_t address)
{
//#ifdef _DEBUG
//	Serial.println(vl53L0X.getAddress());
//#endif
	vl53L0X.setAddress(address);
	if (!vl53L0X.init())
	{
		Serial.println("this->_isSensorOnError = true");
		while (1) {}
	}
	
	vl53L0X.setMeasurementTimingBudget(20000);
	vl53L0X.startContinuous();
}

uint16_t VL53L0XRepository::getMillimetersDistance()
{
		uint16_t distance = vl53L0X.readRangeContinuousMillimeters();
		if (vl53L0X.timeoutOccurred()) {
			Serial.println("this->_isSensorOnError = true");
			this->_isSensorOnError = true; }
		return distance;
}

void VL53L0XRepository::setAddress(uint8_t address)
{
	vl53L0X.setAddress(address);
}


uint8_t VL53L0XRepository::getAddress()
{
	/*	return _sensor->getAddress();*/
}

bool VL53L0XRepository::isSensorOnError()
{
	return this->_isSensorOnError;
}

