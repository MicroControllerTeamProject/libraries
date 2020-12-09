#include "TemperatureDallasActivity.h"
#include <OneWire.h>


OneWire* oneWire;
DallasTemperature* sensors;
auto _temperatureSensorAddress = new uint8_t[0][8];

TemperatureDallasActivity::TemperatureDallasActivity(uint8_t digitalPin) { //: DeviceActivity(digitalPort, digitalPortsNumber) {
	oneWire = new OneWire(digitalPin);
	sensors = new DallasTemperature(oneWire);

	getOnlyDeviceNumber();
	_temperatureSensorAddress = new uint8_t[_numberOfTemperatureSensor][8];
	discoverOneWireDevices();
}

int TemperatureDallasActivity::getHexFromString(String hexstr) {
	return (int)strtol(hexstr.c_str(), 0, 16);
}

void TemperatureDallasActivity::getOnlyDeviceNumber() {
	byte addr[8];
	char probeAddressHexValue[5];
	char value[5];
	this->_numberOfTemperatureSensor = 0;
	while (oneWire->search(addr)) {
		_numberOfTemperatureSensor++;
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
	this->_numberOfTemperatureSensor = 0;
	while (oneWire->search(addr)) {
		for (byte i = 0; i < 8; i++) {
			strcpy(probeAddressHexValue, "0x");
			if (addr[i] < 16) {
				strcat(probeAddressHexValue, "0");
			}
			String(addr[i], HEX).toCharArray(value, 5);
			strcat(probeAddressHexValue, value);
			_temperatureSensorAddress[_numberOfTemperatureSensor][i] = getHexFromString(probeAddressHexValue);
			Serial.print(probeAddressHexValue);
			if (i < 7) {
				Serial.print(", ");
			}
			else
			{
				_numberOfTemperatureSensor++;
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

///void TemperatureDallasActivity::printTemperature(DeviceAddress deviceAddress)
//{
//	float tempC = sensors->getTempC(deviceAddress);
//	if (tempC == -127.00)
//	{
//		Serial.print("Error getting temperature  ");
//	}
//	else
//	{
//		Serial.print("C: ");
//		Serial.print(tempC);
//		/*Serial.print(" F: ");
//		Serial.print(DallasTemperature::toFahrenheit(tempC));*/
//	}
//}

bool TemperatureDallasActivity::isThereAnyCustomMisureOnAlarm(float minCustomValue, float maxCustomValue, String measureDescription) {
	float temperature = 0;
	sensors->begin();
	for (int i = 0; i < _numberOfTemperatureSensor; i++)
	{
		DeviceAddress probe = { _temperatureSensorAddress[i][0],
								_temperatureSensorAddress[i][1],
								_temperatureSensorAddress[i][2],
								_temperatureSensorAddress[i][3],
								_temperatureSensorAddress[i][4],
								_temperatureSensorAddress[i][5],
								_temperatureSensorAddress[i][6],
								_temperatureSensorAddress[i][7]
		};
		temperature = checkTemperatureFromAllProbe(probe);
		Serial.print("temperatura probe "); Serial.print(i); Serial.print(" "); Serial.println(temperature);
		if ((temperature < minCustomValue) || (temperature > maxCustomValue))
		{
			return true;
		}
	}
	return false;

}


float TemperatureDallasActivity::checkTemperatureFromAllProbe(DeviceAddress probe)
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