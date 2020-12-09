#pragma once
#include "DeviceActivity.h"
#include <DallasTemperature.h>

class TemperatureDallasActivity : public DeviceActivity
{
public:
	TemperatureDallasActivity::TemperatureDallasActivity(uint8_t digitalPin);
	int getHexFromString(String hexstr);
	void getOnlyDeviceNumber();
	void discoverOneWireDevices();
	//void  printTemperature(DeviceAddress deviceAddress);
	bool isThereAnyCustomMisureOnAlarm(float maxCustomValue, float minCustomValue, String measureDescription);
	float checkTemperatureFromAllProbe(DeviceAddress probe);
private:
	uint8_t _numberOfTemperatureSensor = 0;
	
};

