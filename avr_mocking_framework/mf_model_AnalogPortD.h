#pragma once  
#include <mf_model_AnalogPortB.h>
class AnalogPortD : public AnalogPortB {
public:
	AnalogPortD(char group_id, const uint8_t pin, uint16_t max_digital_alarm_value_in, uint16_t min_digital_alarm_value_in);
	uint16_t getMaxDigitalAlarmValueIn() const;
	uint16_t getMinDigitalAlarmValueIn() const;
private:
	uint16_t max_digital_alarm_value_in = 0;
	uint16_t min_digital_alarm_value_in = 0;
};
