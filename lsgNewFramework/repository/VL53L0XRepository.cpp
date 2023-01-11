#include "VL53L0XRepository.h"

VL53L0X sensor;
VL53L0XRepository::VL53L0XRepository()
{
	if (!sensor.init())
	{
		Serial.println(this->_isSensorOnError = true);
		while (1) {}
	}
	sensor.setMeasurementTimingBudget(20000);
	sensor.startContinuous();
}

uint16_t VL53L0XRepository::getMillimetersDistance()
{
	uint16_t distance = sensor.readRangeContinuousMillimeters();
	if (sensor.timeoutOccurred()) { this->_isSensorOnError = true; }
}

bool VL53L0XRepository::isSensorOnError()
{
	return this->_isSensorOnError;
}
