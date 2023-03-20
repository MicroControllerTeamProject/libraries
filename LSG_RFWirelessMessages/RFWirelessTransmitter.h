#pragma once
#include <Arduino.h>
#include <pins_arduino.h>
#include <VirtualWire.h>
enum SensorStatus{
	OK,
	KO,
	UNDEFINED
};

enum SensorType{
	SMOK,
	FLAM,
	TEMP,
	GAS,
	HUM,
};

class RFWirelessTransmitter 
{
private:
	uint8_t _tx_pin;
	uint8_t _ptt_pin;
	uint16_t _vw_speed;
	char*	_deviceUID;
	void initDeviceTrasmission(char deviceId[2], char sensorId[2], float numberOfMessages);
public:
	RFWirelessTransmitter(uint8_t tx_pin, uint8_t ptt_pin, uint16_t vw_speed);
	~RFWirelessTransmitter();
	//void SendSensorData(SensorType sensorType, float data, SensorStatus sensorStatus);

	void sendSimpleMessage(char message[2]);

	void sendBufferData(
		char deviceID[2], 
		char sensorId[2],
		char sensorType[1], 
		float sensorValue, 
		char isAlarmOn[1],
		char isBridgeTrasmition[1]
		);

	//void SendTrasmissionStatus();
	//void ResetTrasmissionData();
	void begin();
	void sendBufferData(char message[VW_MAX_MESSAGE_LEN]);
	void startTrasmission(char deviceId[2], char sensorId[2], float numberOfMessages);
	void endTrasmission(char deviceId[2], char sensorId[2]);
};

