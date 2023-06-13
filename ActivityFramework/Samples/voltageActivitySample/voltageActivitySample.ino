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

void setup()
{
#if defined(__AVR_ATmega328P__)
	Serial.begin(9600);
#endif

#if defined(__AVR_ATmega328P__)
  #define pin_Led 13;
  pinMode(13, OUTPUT);
#else if defined (__AVR_ATtiny85__)
  pinMode(0, OUTPUT);
  #define pin_Led 0;
#endif
	
	listOfBatteryAnalogPorts[0] = AnalogPort("BA0", 4);
	listOfBatteryAnalogPorts[0].isEnable = true;
	listOfBatteryAnalogPorts[0].maxVoltageAlarmValueIn = 4.30f;
	listOfBatteryAnalogPorts[0].minVoltageAlarmValueIn = 3.25f;
	analogSensor = AnalogPortSensor("SB01", listOfBatteryAnalogPorts, sizeof(listOfBatteryAnalogPorts) / sizeof(listOfBatteryAnalogPorts[0]));
	batteryVoltageActivity = VoltageActivity(avrMicroRepository, analogSensor, 3.70f, commonsLayer::DEFAULT_m);
}

// the loop function runs over and over again until power down or reset
void loop()
{
#if defined(__AVR_ATmega328P__)
	Serial.print("voltage : ");
	Serial.println(batteryVoltageActivity.getVoltage("BA0"));
	Serial.print("graph : ");
	Serial.println(batteryVoltageActivity.getGrafBarLevel("BA0", 3.30, 3.80, 4.30));
#endif
	if (batteryVoltageActivity.isVoltageOutOfRange("BA0"))
	{
    #if defined(__AVR_ATmega328P__)
		digitalWrite(13, HIGH);
		delay(1000);
		digitalWrite(13, LOW);
		delay(1000);
    #endif

    #if defined(__AVR_ATtiny85__)
		digitalWrite(0, HIGH);
		delay(1000);
		digitalWrite(0, LOW);
		delay(1000);
    #endif

		#if defined(__AVR_ATmega328P__)
		Serial.println("problem");
		#endif
	}
	delay(500);
}
