#pragma once
#include <stdint.h>
class IR_ATMEGA_Repository{
public :
	IR_ATMEGA_Repository(uint8_t rx_pin);
	~IR_ATMEGA_Repository();
	bool init();
	bool is_available();
	bool check_received_code(unsigned long code_to_find);
	void resume();
	void send(unsigned long code, int nbits);
	void enable_to_receive();
private:
	uint8_t pin_receiver;
};

