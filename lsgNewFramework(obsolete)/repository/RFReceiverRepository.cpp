#include "RFReceiverRepository.h"
#include <VirtualWire.h>
#include <Arduino.h>

RFReceiverRepository::RFReceiverRepository(uint8_t rx_pin, uint8_t ptt_pin, uint16_t vw_speed){

	_rx_pin = rx_pin;
	_ptt_pin = ptt_pin;
	_vw_speed = vw_speed;
}

RFReceiverRepository::~RFReceiverRepository(){
}

void RFReceiverRepository::begin()
{
	vw_set_ptt_pin(_ptt_pin);
	vw_set_ptt_inverted(false);
	vw_set_rx_pin(_rx_pin);
	vw_setup(_vw_speed);
	vw_rx_start();
}

void RFReceiverRepository::stop()
{
	vw_setup(0);
	vw_rx_stop();
}

uint8_t* RFReceiverRepository::getMessage()
{
	uint8_t message[3];
	byte messageLength = 3; 
	//vw_wait_rx_max(5000);
	/*vw_wait_rx();*/
	if (vw_get_message(message, &messageLength))
	{
		/*Serial.print('#'); Serial.print((const char*)message); Serial.println('#');
		if (strcmp((const char*)message, "B0") == 0)
		{
			Serial.println("OK");
		}*/
		return message;
	}
	return '\0';
}