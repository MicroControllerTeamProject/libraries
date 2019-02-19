#include "RFWirelessTransmitter.h"

//Trasmission for Sensors and probe devices 

RFWirelessTransmitter::RFWirelessTransmitter(uint8_t tx_pin, uint8_t ptt_pin,uint16_t vw_speed)
{
	_tx_pin = tx_pin;
	_ptt_pin = ptt_pin;
	_vw_speed = vw_speed;
}
 
RFWirelessTransmitter::~RFWirelessTransmitter()
{

}


void RFWirelessTransmitter::begin()
{
	vw_set_ptt_pin(_ptt_pin);
	vw_set_ptt_inverted(false);
	vw_set_tx_pin(_tx_pin);
	vw_setup(_vw_speed); // Bits per sec
}

void RFWirelessTransmitter::sendBufferData(char message[3])
{
	vw_send((uint8_t *)message, strlen(message));
	vw_wait_tx();
}

void RFWirelessTransmitter::sendBufferData(char deviceID[2],
	char sensorId[2],
	char sensorType[1],
	float sensorValue,
	char isAlarmOn[1],
	char isBridgeTrasmition[1]
	)
{

	char message[18];   // array to hold the result.
	char stringFloat[8] = "0000.00";
	strcpy(message, "*#"); // copy string one into the result.
	strcat(message, deviceID); // copy string one into the result.
	strcat(message, sensorType); // append string two to the result.
	strcat(message,sensorId); // append string two to the result.
	dtostrf(sensorValue, 7, 2, stringFloat);
	strcat(message, stringFloat);
	strcat(message, isAlarmOn); // append string two to the result.
	strcat(message, isBridgeTrasmition); // append string two to the result.
	strcat(message, "#*"); // copy string one into the result.
	vw_send((uint8_t *)message, 19);
	vw_wait_tx();
	//Serial.println(message);
	//delay(1000);
}

void RFWirelessTransmitter::startTrasmission(char deviceId[2], char sensorId[2], float numberOfMessages)
{
	RFWirelessTransmitter::initDeviceTrasmission(deviceId, sensorId, numberOfMessages);
}

void RFWirelessTransmitter::endTrasmission(char deviceId[2], char sensorId[2])
{
	RFWirelessTransmitter::initDeviceTrasmission(deviceId, sensorId, 0);
}

void RFWirelessTransmitter::initDeviceTrasmission(char deviceId[2],char sensorId[2], float numberOfMessages)
{
	char message[18];  
	char stringFloat[8] = "0000.00";
	strcpy(message, "*#"); 
	strcat(message, deviceId);
	strcat(message, sensorId);
	dtostrf(numberOfMessages, 7, 2, stringFloat);
	strcat(message, stringFloat);
	strcat(message, "#*");
	vw_send((uint8_t *)message, 19);
	vw_wait_tx();
	//Serial.println(message);
}



//void RFWirelessTransmitter::ResetTrasmissionData()
//{
//
//}

