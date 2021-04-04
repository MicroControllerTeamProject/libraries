#pragma once
#include "DeviceActivity.h"
#include <DallasTemperature.h>
#include <Arduino.h>
#include <pins_arduino.h>

class TemperatureDallasActivity : public DeviceActivity
{
public:
	TemperatureDallasActivity(DigitalPort** digitalPort, uint8_t digitalPortsNumber);
	~TemperatureDallasActivity();
	//void  printTemperature(DeviceAddress deviceAddress);
	bool isThereAnyProbeOnAlarm();
	uint8_t getProbeNumbers();
	float getTemperatureFromPobeIndex(uint8_t probeIndex);
private:
	void getOnlyDeviceNumber();
	uint8_t numberOfTemperatureSensor = 0;
	int getHexFromString(String hexstr);
	float getTemperatureFromProbe(DeviceAddress probe);
	void discoverOneWireDevices();
	float getCustomMisureValue();
	OneWire* oneWire;
	DallasTemperature* sensors;
	uint8_t temperatureSensorAddressIndex = 0;
};

