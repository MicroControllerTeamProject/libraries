#pragma once
#include "mf_model_DigitalPort.h"
#include <mf_repository_AvrMicroRepository.h>
#include <stdint.h>
class DigitalPortActivity{
public:
	DigitalPortActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** digitalPort, uint8_t digitalPortsNumber);
	DigitalPortActivity::DigitalPortActivity();
	bool is_any_port_triggered();
	void turn_port_to_level(uint8_t pin, bool level);
	uint8_t get_ports_number();
	DigitalPort** get_digital_ports() {
		return this->digitalPort;
	}
	DigitalPort* get_port_by_pin(uint8_t pin);
private:
	void set_ports_direction();
	uint8_t digital_port_number = 0;
	DigitalPort** digitalPort = {};
	AvrMicroRepository* avrMicroRepository = nullptr;
};

