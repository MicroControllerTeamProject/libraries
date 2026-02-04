#include <mf_model_AnalogPortB.h>
AnalogPortB::AnalogPortB(char group_id, const uint8_t pin) {
	this->group_id = group_id;
	this->pin = pin;
}
char AnalogPortB::get_group_id() { return this->group_id; }
uint8_t AnalogPortB::get_pin() { return this->pin; }
