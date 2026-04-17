
#include <mf_activity_AnalogPortCActivity.h>
AnalogPortCActivity::AnalogPortCActivity(AvrMicroRepository& avrMicroRepository, AnalogPortC** analogPortForCustomMisure, uint8_t analogPortsNumber) :AnalogPortBActivity(avrMicroRepository, analogPortsNumber, (AnalogPortB**)analogPortForCustomMisure) {
	this->analogPortForCustomMisure = analogPortForCustomMisure;
	this->reset_ports();
}
float AnalogPortCActivity::get_unit_of_misure_value_by_index(uint8_t index) {
	if (index >= this->get_analog_ports_number()) {
		return 0.00f;
	}

	AnalogPortC* analog_port = this->analogPortForCustomMisure[index];
	float denominator = analog_port->getIstUnitOfMisureCentered() ? 512.00f : 1023.00f;
	return (analog_port->getFullScaleUnitOfMisure() / denominator) * analog_port->digital_value;
}
bool  AnalogPortCActivity::is_any_port_out_of_range() {
	bool isOnAlarm = false;
	for (int i = 0; i < this->get_analog_ports_number(); i++) {
		float unit_of_misure_value = this->get_unit_of_misure_value_by_index(i); 
#if _DEBUG_FOR_SERIAL
		Serial.print("Cur."); Serial.print(i); Serial.print(" : "); Serial.println(unit_of_misure_value);
#endif

		if (unit_of_misure_value > this->analogPortForCustomMisure[i]->getMaxUnitOfMisureAlarmValue()) {
			this->analogPortForCustomMisure[i]->is_alarm_above_threshold = true;
			this->analogPortForCustomMisure[i]->is_onAlarm = true;
			this->analogPortForCustomMisure[i]->is_time_above_threshold_elapsed = is_delay_elapsed_for_ports_above_threshold(this->analogPortForCustomMisure[i]);
			isOnAlarm = true;
		}
		else if (unit_of_misure_value < this->analogPortForCustomMisure[i]->getMinUnitOfMisureAlarmValue()) {
			this->analogPortForCustomMisure[i]->is_alarm_under_threshold = true;
			this->analogPortForCustomMisure[i]->is_onAlarm = true;
			this->analogPortForCustomMisure[i]->is_time_under_threshold_elapsed = is_delay_elapsed_for_ports_under_threshold(this->analogPortForCustomMisure[i]);
			isOnAlarm = true;
		}
		else {
			this->analogPortForCustomMisure[i]->first_time_on_alarm = 0;
			this->analogPortForCustomMisure[i]->is_time_under_threshold_elapsed = false;
		}
	}
	return isOnAlarm;
}
AnalogPortC** AnalogPortCActivity::get_analog_ports() {
	return this->analogPortForCustomMisure;
}
AnalogPortC* AnalogPortCActivity::get_port_by_pin(uint8_t pin) {
	for (int i = 0; i < this->get_analog_ports_number(); i++) {
		if (this->analogPortForCustomMisure[i]->get_pin() == pin) {
			return this->analogPortForCustomMisure[i];
		}
	}
	return nullptr;
}

