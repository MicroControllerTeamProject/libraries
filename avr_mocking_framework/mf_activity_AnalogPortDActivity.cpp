
#include <mf_activity_AnalogPortDActivity.h>
AnalogPortDActivity::AnalogPortDActivity(AvrMicroRepository& avrMicroRepository, AnalogPortD** analogPortForDigitalMeasure, uint8_t analogPortsNumber):AnalogPortBActivity(avrMicroRepository, analogPortsNumber, (AnalogPortB**)analogPortForDigitalMeasure){
	this->analogPortForDigitalMeasure = analogPortForDigitalMeasure;
	this->reset_ports();
}
bool AnalogPortDActivity::is_any_port_out_of_range() {
	bool isOnAlarm = false;
	for (int i = 0; i < this->get_analog_ports_number(); i++) {
			if (this->analogPortForDigitalMeasure[i]->digital_value > this->analogPortForDigitalMeasure[i]->getMaxDigitalAlarmValueIn()) {
				this->analogPortForDigitalMeasure[i]->is_alarm_above_threshold = true;
				this->analogPortForDigitalMeasure[i]->is_onAlarm = true;
				this->analogPortForDigitalMeasure[i]->is_time_above_threshold_elapsed = is_delay_elapsed_for_ports_above_threshold(this->analogPortForDigitalMeasure[i]);
				isOnAlarm = true;
			}
			else if (this->analogPortForDigitalMeasure[i]->digital_value < this->analogPortForDigitalMeasure[i]->getMinDigitalAlarmValueIn()) {
				this->analogPortForDigitalMeasure[i]->is_alarm_under_threshold = true;
				this->analogPortForDigitalMeasure[i]->is_onAlarm = true;
				this->analogPortForDigitalMeasure[i]->is_time_under_threshold_elapsed = is_delay_elapsed_for_ports_under_threshold(this->analogPortForDigitalMeasure[i]);
				isOnAlarm = true;
			}
			else {
				this->analogPortForDigitalMeasure[i]->first_time_on_alarm = 0;
				this->analogPortForDigitalMeasure[i]->is_time_under_threshold_elapsed = false;
			}
		
	}
	return isOnAlarm;
}
AnalogPortD** AnalogPortDActivity::get_analog_ports() {
	return this->analogPortForDigitalMeasure;
}
AnalogPortD* AnalogPortDActivity::get_port_by_pin(uint8_t pin) {
	for (int i = 0; i < this->get_analog_ports_number(); i++) {
		if (this->analogPortForDigitalMeasure[i]->get_pin() == pin) {
			return this->analogPortForDigitalMeasure[i];
		}
	}
}

