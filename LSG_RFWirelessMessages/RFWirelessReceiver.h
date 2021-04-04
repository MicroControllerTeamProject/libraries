#pragma once
#include <arduino.h>
#include <pins_arduino.h>
#include <VirtualWire.h>

class RFWirelessReceiver
{

private:
	uint8_t _rx_pin;
	uint8_t _ptt_pin;
	uint16_t _vw_speed;
	uint8_t _receivingItems;
	uint8_t _receivedItems;
	String _rxStart;
	String _deviceId;
	String _sensorType;
	String _sensorId;
	String _sensorStatus;
	String _sensorValue;
	String _isAlarmOn;
	String _isBridgeTrasmition;
	String _rxEnd;

public:
	RFWirelessReceiver(uint8_t tx_pin, uint8_t ptt_pin, uint16_t vw_speed);
	~RFWirelessReceiver();
	String GetMessage(char deviceId[2], char sensorId[2]);
	String GetMessage();
	void begin();
	String GetStartProtocol();
	void ResetAllVariables();
	String GetEndProtocol();
	String GetDeviceId();
	String GetSensorType();
	String GetSensorID();
	String GetSensorValue();
	String GetIsOnAlarm();
	String GetIsOnBridgeTrasmition();
	String GetSimpleMessage();

};

