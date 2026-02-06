#pragma once  
#include <stdint.h>
class AnalogPortB {
public:
	AnalogPortB(char group_id, const uint8_t pin);
	virtual ~AnalogPortB() =0;
	uint16_t digital_value = 0;
	bool is_enabled = true;
	bool is_on_error = false;
	bool is_onAlarm = false;
	bool is_alarm_above_threshold = false;
	bool is_alarm_under_threshold = false;
	uint16_t set_alarm_if_under_threshold_for_seconds = 0;
	uint16_t set_alarm_if_above_threshold_for_seconds = 0;
	unsigned long first_time_on_alarm = 0;
	bool is_time_under_threshold_elapsed = false;
	bool is_time_above_threshold_elapsed = false;
	uint16_t offset = 0;
	char get_group_id();
	uint8_t get_pin();
private:
	char group_id = {};
	uint8_t pin;
};
inline AnalogPortB::~AnalogPortB() {}

