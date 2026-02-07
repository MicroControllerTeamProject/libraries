#include <mf_model_AnalogPortD.h>
AnalogPortD::AnalogPortD(char group_id, const uint8_t pin, uint16_t max_digital_alarm_value_in, uint16_t min_digital_alarm_value_in):AnalogPortB(group_id, pin){
	this->max_digital_alarm_value_in = max_digital_alarm_value_in;
	this->min_digital_alarm_value_in = min_digital_alarm_value_in;
}
uint16_t AnalogPortD::getMaxDigitalAlarmValueIn() const { return this->max_digital_alarm_value_in;}
uint16_t AnalogPortD::getMinDigitalAlarmValueIn() const { return this->min_digital_alarm_value_in; }
