/*
 Name:		test_lsgNewFramework.ino
 Created:	1/19/2023 11:44:53 AM
 Author:	luigi.santagada
*/
#include <VoltageActivity.h>
#include <DeviceActivity.h>
#include <AvrMicroRepository.h>
#include <AnalogPortSensor.h>
#include <Arduino.h>


AnalogPort listOfBatteryAnalogPorts[1];
AvrMicroRepository avrMicroRepository(19200);
AnalogPortSensor analogSensor;
VoltageActivity batteryVoltageActivity;

void setup() {
	Serial.begin(9600);
	listOfBatteryAnalogPorts[0] =  AnalogPort("BA0", A1);
	listOfBatteryAnalogPorts[0].isEnable = true;
	listOfBatteryAnalogPorts[0].maxVoltageAlarmValueIn = 4.30f;
	listOfBatteryAnalogPorts[0].minVoltageAlarmValueIn = 3.25f;
	analogSensor = AnalogPortSensor("SB01",listOfBatteryAnalogPorts, sizeof(listOfBatteryAnalogPorts) / sizeof(listOfBatteryAnalogPorts[0]));
	batteryVoltageActivity = VoltageActivity(avrMicroRepository, analogSensor, 4.80f, commonsLayer::DEFAULT_m);
}

// the loop function runs over and over again until power down or reset
void loop() {
 
	Serial.print("voltage : "); Serial.println(batteryVoltageActivity.getVoltage("BA0"));
	Serial.print("graph : "); Serial.println(batteryVoltageActivity.getGrafBarLevel("BA0",3.30,3.80,4.30));
	if (batteryVoltageActivity.isVoltageOutOfRange("BA0"))
	{
		Serial.println("problem");
	}
	delay(500);
}
