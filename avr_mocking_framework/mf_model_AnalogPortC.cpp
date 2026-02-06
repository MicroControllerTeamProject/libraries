#include <mf_model_AnalogPortC.h>
AnalogPortC::AnalogPortC(char group_id, const uint8_t pin, float full_scale_unit_of_misure, float max_unit_of_misure_alarm_value, float min_unit_of_misure_alarm_value, bool unit_of_misure_is_centered):AnalogPortB(group_id,pin) {
	this->max_unit_of_misure_alarm_value = max_unit_of_misure_alarm_value;
	this->min_unit_of_misure_alarm_value = min_unit_of_misure_alarm_value;
	this->full_scale_unit_of_misure = full_scale_unit_of_misure;
	this->unit_of_misure_is_centered = unit_of_misure_is_centered;
}
AnalogPortC::AnalogPortC(char group_id, const uint8_t pin, float max_unit_of_misure_alarm_value, float min_unit_of_misure_alarm_value) : AnalogPortC(group_id, pin, 0.00f, max_unit_of_misure_alarm_value, min_unit_of_misure_alarm_value, false) {}
float    AnalogPortC::getFullScaleUnitOfMisure() const { return this->full_scale_unit_of_misure; }
bool     AnalogPortC::getIstUnitOfMisureCentered() const { return this->unit_of_misure_is_centered; }
float    AnalogPortC::getMaxUnitOfMisureAlarmValue() const { return this->max_unit_of_misure_alarm_value; }
float    AnalogPortC::getMinUnitOfMisureAlarmValue() const { return this->min_unit_of_misure_alarm_value; }

