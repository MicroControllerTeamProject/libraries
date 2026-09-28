// File: mf_activity_AnalogPortCActivity.cpp
#include <mf_activity_AnalogPortCActivity.h>

AnalogPortCActivity::AnalogPortCActivity(AvrMicroRepository& avrMicroRepository, AnalogPortC** analogPortForCustomMisure, uint8_t analogPortsNumber)
	: AnalogPortBActivity(avrMicroRepository, analogPortsNumber, (AnalogPortB**)analogPortForCustomMisure) {
	this->analogPortForCustomMisure = analogPortForCustomMisure;
	this->reset_ports();
}

float AnalogPortCActivity::get_unit_of_misure_value_by_index(uint8_t index) {
	if (index >= this->get_analog_ports_number()) {
		return 0.00f;
	}

	AnalogPortC* analog_port = this->analogPortForCustomMisure[index];

	if (analog_port->getIstUnitOfMisureCentered()) {
		float sensitivity_volt = analog_port->getUnitOfMisureSensitivityVolt();

		if (sensitivity_volt > 0.0f) {
			float adc_step_volt = this->get_avr_micro_repository()->get_vref() / 1023.0f;
			float delta_voltage = adc_step_volt * (float)analog_port->signed_digital_value;
			return delta_voltage / sensitivity_volt;
		}

		return (analog_port->getFullScaleUnitOfMisure() / 512.00f) * (float)analog_port->signed_digital_value;
	}

	return (analog_port->getFullScaleUnitOfMisure() / 1023.00f) * (float)analog_port->digital_value;
}

bool AnalogPortCActivity::is_any_port_out_of_range() {
	bool isOnAlarm = false;

	for (int i = 0; i < this->get_analog_ports_number(); i++) {
		float unit_of_misure_value = this->get_unit_of_misure_value_by_index(i);

#if _DEBUG_FOR_SERIAL
		Serial.print(F("Cur."));
		Serial.print(i);
		Serial.print(F(" : "));
		Serial.println(unit_of_misure_value);
#endif

		if (unit_of_misure_value > this->analogPortForCustomMisure[i]->getMaxUnitOfMisureAlarmValue()) {
#if _DEBUG_FOR_SERIAL
			bool was_elapsed = this->analogPortForCustomMisure[i]->is_time_above_threshold_elapsed;
#endif
			if (!this->analogPortForCustomMisure[i]->is_alarm_above_threshold) {
				this->analogPortForCustomMisure[i]->first_time_on_alarm = 0;
			}
			this->analogPortForCustomMisure[i]->is_alarm_above_threshold = true;
			this->analogPortForCustomMisure[i]->is_alarm_under_threshold = false;
			this->analogPortForCustomMisure[i]->is_onAlarm = true;
			this->analogPortForCustomMisure[i]->is_time_under_threshold_elapsed = false;
			this->analogPortForCustomMisure[i]->is_time_above_threshold_elapsed = is_delay_elapsed_for_ports_above_threshold(this->analogPortForCustomMisure[i]);
#if _DEBUG_FOR_SERIAL
			if (!was_elapsed && this->analogPortForCustomMisure[i]->is_time_above_threshold_elapsed) {
				Serial.print(F("ALM CUR HIGH ")); Serial.println(this->analogPortForCustomMisure[i]->get_group_id());
			}
#endif
			isOnAlarm = true;
		}
		else if (unit_of_misure_value < this->analogPortForCustomMisure[i]->getMinUnitOfMisureAlarmValue()) {
#if _DEBUG_FOR_SERIAL
			bool was_elapsed = this->analogPortForCustomMisure[i]->is_time_under_threshold_elapsed;
#endif
			if (!this->analogPortForCustomMisure[i]->is_alarm_under_threshold) {
				this->analogPortForCustomMisure[i]->first_time_on_alarm = 0;
			}
			this->analogPortForCustomMisure[i]->is_alarm_above_threshold = false;
			this->analogPortForCustomMisure[i]->is_alarm_under_threshold = true;
			this->analogPortForCustomMisure[i]->is_onAlarm = true;
			this->analogPortForCustomMisure[i]->is_time_above_threshold_elapsed = false;
			this->analogPortForCustomMisure[i]->is_time_under_threshold_elapsed = is_delay_elapsed_for_ports_under_threshold(this->analogPortForCustomMisure[i]);
#if _DEBUG_FOR_SERIAL
			if (!was_elapsed && this->analogPortForCustomMisure[i]->is_time_under_threshold_elapsed) {
				Serial.print(F("ALM CUR LOW ")); Serial.println(this->analogPortForCustomMisure[i]->get_group_id());
			}
#endif
			isOnAlarm = true;
		}
		else {
			this->analogPortForCustomMisure[i]->is_onAlarm = false;
			this->analogPortForCustomMisure[i]->is_alarm_above_threshold = false;
			this->analogPortForCustomMisure[i]->is_alarm_under_threshold = false;
			this->analogPortForCustomMisure[i]->first_time_on_alarm = 0;
			this->analogPortForCustomMisure[i]->is_time_under_threshold_elapsed = false;
			this->analogPortForCustomMisure[i]->is_time_above_threshold_elapsed = false;
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
