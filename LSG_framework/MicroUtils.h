#pragma once
#include <Arduino.h>
#include <pins_arduino.h>

class MicroUtils
{
public:
	static String getBatteryGrafBarLevel(float batteryVoltageLevel);
	static float internalTemperature(unsigned int offset);
};

