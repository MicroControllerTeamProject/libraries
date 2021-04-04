#include "RFWirelessReceiver.h"

RFWirelessReceiver::RFWirelessReceiver(uint8_t rx_pin, uint8_t ptt_pin, uint16_t vw_speed)
{
	_rx_pin = rx_pin;
	_ptt_pin = ptt_pin;
	_vw_speed = vw_speed;
}

RFWirelessReceiver::~RFWirelessReceiver()
{
}

void RFWirelessReceiver::begin()
{
	vw_set_ptt_pin(_ptt_pin);
	vw_set_ptt_inverted(false);
	vw_set_rx_pin(_rx_pin);
	vw_setup(_vw_speed); // Bits per sec
	vw_rx_start();
}

String RFWirelessReceiver::GetStartProtocol()
{
	return _rxStart;
}

String RFWirelessReceiver::GetEndProtocol()
{
	return _rxEnd;
}

String RFWirelessReceiver::GetDeviceId()
{
	return _deviceId;
}

String RFWirelessReceiver::GetSensorType()
{
	return _sensorType;
}

String RFWirelessReceiver::GetSensorID()
{
	return _sensorId;
}

String RFWirelessReceiver::GetSensorValue()
{
	return _sensorValue;
}

String RFWirelessReceiver::GetIsOnAlarm()
{
	return _isAlarmOn;
}

String RFWirelessReceiver::GetIsOnBridgeTrasmition()
{
	return _isBridgeTrasmition;
}

String RFWirelessReceiver::GetMessage(char deviceId[2], char sensorId[2])
{
	ResetAllVariables();

	//Serial.println("chiamata");
	String deviceIdString = deviceId;

	String sensorIdString = sensorId;

	String rxStartString = "*#";

	String rxEndString = "#*";

	byte message[19];

	byte messageLength = 19; // the size of the message
	
	//vw_wait_rx_max(5000);

	//vw_wait_rx();

	if (vw_get_message(message, &messageLength)) // Non-blocking
	{
		//Serial.println("Received data: ");
		String messageString = (const char *)message;
		messageString.trim();
	
		/*Serial.println(messageString);
		Serial.println(messageString.length());

		Serial.println(deviceIdString);
		Serial.println(sensorIdString);*/

		if (messageString.length() == 15
			&& messageString.substring(0, 2) == rxStartString
			&& messageString.substring(2, 4) == deviceIdString
			&& messageString.substring(4, 6) == sensorIdString
			&& messageString.substring(13, 15) == rxEndString
			&& messageString.substring(6, 13).toFloat() != 0
			)
		{
			_deviceId = messageString.substring(2, 4);
			_sensorId = messageString.substring(4, 6);
			_receivedItems = 0;
			_receivingItems = messageString.substring(6, 13).toFloat();
			//Serial.println(_trasmitionItems);
			//Serial.println("init device transmission");
			return "init device transmission";
		}

		
		if (messageString.length() == 15
			&& messageString.substring(0, 2) == rxStartString
			&& messageString.substring(2, 4) == deviceIdString
			&& messageString.substring(4, 6) == sensorIdString
			&& messageString.substring(13, 15) == rxEndString
			&& messageString.substring(6, 13).toFloat() == 0.00
			)
		{
			//Serial.println("Fine trasmissione");
			if (_receivedItems == _receivingItems)
			{
				return "OK";

			}
			else
			{
				return "KO";
			}
		}

		if (messageString.length() == 18
			&& messageString.substring(2, 4) == deviceIdString 
			&& messageString.substring(0, 2) == rxStartString
			&& messageString.substring(16, 18) == rxEndString 
			&& messageString.substring(5, 7) == sensorIdString
			)
		{
			//Serial.println(messageString);

			_rxStart = messageString.substring(0, 2);
			_deviceId = messageString.substring(2, 4);	
			_sensorType = messageString.substring(4, 5);		
			_sensorId = messageString.substring(5, 7);	
			_sensorValue = messageString.substring(7, 14);
			_isAlarmOn = messageString.substring(14, 15); 
			_isBridgeTrasmition = messageString.substring(15, 16);
			_rxEnd = messageString.substring(16, 18);
			_receivedItems++;
			return messageString;
		}
		else
		{
			return "";
		}
	}
	else
	{
		return "";
	}
}

String RFWirelessReceiver::GetMessage()
{
	//Serial.println("chiamata");
	
	String rxStartString = "*#";

	String rxEndString = "#*";

	byte message[19];

	byte messageLength = 19; // the size of the message

	//vw_wait_rx_max(5000);

	//vw_wait_rx();

	if (vw_get_message(message, &messageLength)) // Non-blocking
	{
		String messageString = (const char *)message;
		messageString.trim();



		if (messageString.length() == 15
			&& messageString.substring(0, 2) == rxStartString
			/*&& messageString.substring(2, 4) == deviceIdString
			&& messageString.substring(4, 6) == sensorIdString*/
			&& messageString.substring(13, 15) == rxEndString
			&& messageString.substring(6, 13).toFloat() != 0
			)
		{
			_deviceId = messageString.substring(2, 4);
			_sensorId = messageString.substring(4, 6);
			_receivedItems = 0;
			_receivingItems = messageString.substring(6, 13).toFloat();
			//Serial.println(_trasmitionItems);
			//Serial.println("init device transmission");
			return "init device transmission";
		}

		if (messageString.length() == 15
			&& messageString.substring(0, 2) == rxStartString
			&& messageString.substring(2, 4) == _deviceId
			&& messageString.substring(4, 6) == _sensorId
			&& messageString.substring(13, 15) == rxEndString
			&& messageString.substring(6, 13).toFloat() == 0.00
			)
		{
			//Serial.println("Fine trasmissione");
			if (_receivedItems == _receivingItems)
			{
				return "OK";
				ResetAllVariables();
			}
			else
			{
				return "KO";
				ResetAllVariables();
			}
		}

		if (messageString.length() == 18
			&& messageString.substring(2, 4) == _deviceId
			&& messageString.substring(0, 2) == rxStartString
			&& messageString.substring(16, 18) == rxEndString
			&& messageString.substring(5, 7) == _sensorId
			)
		{
			//Serial.println(messageString);

			_rxStart = messageString.substring(0, 2);
			/*_deviceID = messageString.substring(2, 4);*/
			_sensorType = messageString.substring(4, 5);
			/*_sensorId = messageString.substring(5, 7);*/
			_sensorValue = messageString.substring(7, 14);
			_isAlarmOn = messageString.substring(14, 15);
			_isBridgeTrasmition = messageString.substring(15, 16);
			_rxEnd = messageString.substring(16, 18);
			_receivedItems++;
			return messageString;
		}
		else
		{
			return "";
		}
	}
	else
	{
		return "";
	}
}

String RFWirelessReceiver::GetSimpleMessage()
{
	//Serial.println("chiamata");

	byte message[3];

	byte messageLength = 3; // the size of the message

	//vw_wait_rx_max(5000);

	//vw_wait_rx();

	if (vw_get_message(message, &messageLength)) // Non-blocking
	{

		String messageString = (const char*)message;
		messageString.trim();

		return messageString;
	}
	return "";
}

void RFWirelessReceiver::ResetAllVariables()
{
	_rxStart = "";
	_deviceId = "";
	_sensorType = "";
	_sensorId = "";
	_sensorStatus = "";
	_sensorValue = "";
	_isAlarmOn = "";
	_isBridgeTrasmition = "";
	_rxEnd  = "";
	_receivedItems = 0;
	_receivingItems = 0;
}