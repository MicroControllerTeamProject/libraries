#pragma once
#include "DeviceActivity.h"
#include <DallasTemperature.h>
#include <Arduino.h>
#include <pins_arduino.h>

class TemperatureDallasActivity : public DeviceActivity
{
public:
	TemperatureDallasActivity::TemperatureDallasActivity(uint8_t digitalPin);

	
	//void  printTemperature(DeviceAddress deviceAddress);
	bool isThereAnyCustomMisureOnAlarm(byte minCustomValue, byte maxCustomValue, String measureDescription);
	void getOnlyDeviceNumber();
private:
	uint8_t _numberOfTemperatureSensor = 0;
	int getHexFromString(String hexstr);
	float getTemperatureFromProbe(DeviceAddress probe);
	
	void discoverOneWireDevices();

	
	
	
};

