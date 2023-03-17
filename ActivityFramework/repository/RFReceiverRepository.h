#pragma once
#include <stdint.h>
class RFReceiverRepository
{
public:
	RFReceiverRepository(uint8_t rx_pin, uint8_t ptt_pin, uint16_t vw_speed);
	~RFReceiverRepository();
	virtual void begin();
	virtual void stop();
	virtual uint8_t* getMessage();
private:
	uint8_t _rx_pin;
	uint8_t _ptt_pin;
	uint16_t _vw_speed;

	
};

