#include "VL53L0XRepository.h"
#include <VL53L0X.h>

VL53L0X sensor;
VL53L0XRepository::VL53L0XRepository()
{
	if (!sensor.init())
	{
		Serial.println(F("error sensor!"));
		while (1) {}
	}
	sensor.setMeasurementTimingBudget(20000);
	sensor.startContinuous();
}

uint16_t VL53L0XRepository::getMillimetersDistance()
{
	uint16_t distance = sensor.readRangeContinuousMillimeters();
	if (sensor.timeoutOccurred()) { lcdPrintMessage(F("sensor error"), 0, 4, false); }
}
