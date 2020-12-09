#pragma once
#include <Arduino.h>
#include <pins_arduino.h>


//enum Direction
//	{
//		input,
//		output
//	};

class AnalogPort
{
public:
	AnalogPort(String uid, uint8_t pin);
	/*AnalogPort(String uid, uint8_t pin, Direction direction, float	maxVoltageAlarmValueIn, float minVoltageAlarmValueIn);
	AnalogPort(String uid, uint8_t pin, Direction direction, int maxAlarmValueIn, int minAlarmValueIn);
	AnalogPort(String uid, uint8_t pin, Direction direction, int maxAlarmValueIn, int minAlarmValueIn);
	AnalogPort(String uid, uint8_t pin, Direction direction, float unitOfMisureFullScale , float maxUnitOfMisureAlarmValue, float minUnitOfMisureAlarmValue);
	*/
	//enum AlarmOn
	//{
	//    low,
	//    high
	//};

	String uid;
	bool isEnable = true;
	uint8_t pin;
	//Direction direction = input;
	//AlarmOn alarmOn = low;
	//bool isOnPullUp = false;

	///Voltage value 0-5V
	float	 maxVoltageAlarmValueIn = 5;
	///Voltage value 0-5V
	float	 minVoltageAlarmValueIn = 0;
	///scalar bit value 0 - 1023
	int	 maxAlarmValueIn = 1023;
	///scalar bit value 0 - 1023
	int	 minAlarmValueIn = 0;
	///Max value of scale differente to voltage or scalar bit value
	///Example: value of current for a current sensor.
	float unitOfMisureFullScale = 0;
	float maxUnitOfMisureAlarmValue = 0;
	float minUnitOfMisureAlarmValue = 0;

};
