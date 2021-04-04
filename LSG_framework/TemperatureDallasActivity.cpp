#include "TemperatureDallasActivity.h"
#include <OneWire.h>

auto _temperatureSensorAddress = new uint8_t[0][8];

TemperatureDallasActivity::TemperatureDallasActivity(DigitalPort** digitalPort, uint8_t digitalPortsNumber) : DeviceActivity(digitalPort, digitalPortsNumber) {
	oneWire = new OneWire(this->digitalPort[0]->getPin());
	sensors = new DallasTemperature(oneWire);
	
	getOnlyDeviceNumber();
	_temperatureSensorAddress = new uint8_t[numberOfTemperatureSensor][8];
	discoverOneWireDevices();
}

TemperatureDallasActivity::~TemperatureDallasActivity()
{
	delete oneWire;
	delete sensors;
}

int TemperatureDallasActivity::getHexFromString(String hexstr) {
	return (int)strtol(hexstr.c_str(), 0, 16);
}

void TemperatureDallasActivity::getOnlyDeviceNumber() {
	byte addr[8];
	char probeAddressHexValue[5];
	char value[5];
	this->numberOfTemperatureSensor = 0;
	while (oneWire->search(addr)) {
		numberOfTemperatureSensor++;
		if (OneWire::crc8(addr, 7) != addr[7]) {
			Serial.print("CRC is not valid!\n");
			return;
		}
	}
	oneWire->reset_search();
	return;
}

void TemperatureDallasActivity::discoverOneWireDevices() {
	byte addr[8];
	char probeAddressHexValue[5];
	char value[5];
	this->numberOfTemperatureSensor = 0;
	while (oneWire->search(addr)) {
		for (byte i = 0; i < 8; i++) {
			strcpy(probeAddressHexValue, "0x");
			if (addr[i] < 16) {
				strcat(probeAddressHexValue, "0");
			}
			String(addr[i], HEX).toCharArray(value, 5);
			strcat(probeAddressHexValue, value);
			_temperatureSensorAddress[numberOfTemperatureSensor][i] = getHexFromString(probeAddressHexValue);
			Serial.print(probeAddressHexValue);
			if (i < 7) {
				Serial.print(", ");
			}
			else
			{
				numberOfTemperatureSensor++;
				Serial.println();
			}
		}
		if (OneWire::crc8(addr, 7) != addr[7]) {
			Serial.print("CRC is not valid!\n");
			return;
		}
	}
	oneWire->reset_search();
	return;
}

float TemperatureDallasActivity::getTemperatureFromPobeIndex(uint8_t deviceIndex)
{
	DeviceAddress probe = { _temperatureSensorAddress[deviceIndex][0],
								_temperatureSensorAddress[deviceIndex][1],
								_temperatureSensorAddress[deviceIndex][2],
								_temperatureSensorAddress[deviceIndex][3],
								_temperatureSensorAddress[deviceIndex][4],
								_temperatureSensorAddress[deviceIndex][5],
								_temperatureSensorAddress[deviceIndex][6],
								_temperatureSensorAddress[deviceIndex][7]
	};
	return getTemperatureFromProbe(probe);
}

bool TemperatureDallasActivity::isThereAnyProbeOnAlarm()
{
	bool returnValue = false;
	sensors->begin();
	temperatureSensorAddressIndex = 0;
	while (temperatureSensorAddressIndex < numberOfTemperatureSensor)
	{
		if (this->isThereAnyCustomMisureOnAlarm()) { 
			returnValue = true; }
		temperatureSensorAddressIndex++;
	}
	return returnValue;
	/*for (_temperatureSensorAddressIndex; i < _numberOfTemperatureSensor; i++)
	{
		this->isThereAnyCustomMisureOnAlarm();
	}*/
}

float TemperatureDallasActivity::getCustomMisureValue()
{
		DeviceAddress probe = { _temperatureSensorAddress[temperatureSensorAddressIndex][0],
								_temperatureSensorAddress[temperatureSensorAddressIndex][1],
								_temperatureSensorAddress[temperatureSensorAddressIndex][2],
								_temperatureSensorAddress[temperatureSensorAddressIndex][3],
								_temperatureSensorAddress[temperatureSensorAddressIndex][4],
								_temperatureSensorAddress[temperatureSensorAddressIndex][5],
								_temperatureSensorAddress[temperatureSensorAddressIndex][6],
								_temperatureSensorAddress[temperatureSensorAddressIndex][7]
		};
		//Serial.print("temperatura probe "); Serial.print(_temperatureSensorAddressIndex); Serial.print(" "); Serial.println(getTemperatureFromProbe(probe));
		return getTemperatureFromProbe(probe);
}

float TemperatureDallasActivity::getTemperatureFromProbe(DeviceAddress probe)
{
	sensors->begin();
	/*for (int i = 0; i < _numberOfTemperatureSensor; i++)
	{
		DeviceAddress probe = { _temperatureSensorAddress[i][0],
								_temperatureSensorAddress[i][1],
								_temperatureSensorAddress[i][2],
								_temperatureSensorAddress[i][3],
								_temperatureSensorAddress[i][4],
								_temperatureSensorAddress[i][5],
								_temperatureSensorAddress[i][6],
								_temperatureSensorAddress[i][7]
		};*/
	sensors->setResolution(probe, 10);
	//delay(1000);
	/*Serial.println();
	Serial.print("Getting temperature from number "); Serial.print(i); Serial.println(" probe");*/
	sensors->requestTemperatures();
	//Serial.print("temperature is:   ");
	//printTemperature(probe);
	return sensors->getTempC(probe);

}

uint8_t TemperatureDallasActivity::getProbeNumbers()
{
	return this->numberOfTemperatureSensor;
}