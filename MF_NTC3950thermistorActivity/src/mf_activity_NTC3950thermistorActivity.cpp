#include <mf_activity_NTC3950thermistorActivity.h>
#if _DEBUG_FOR_SERIAL
#include <Arduino.h>
#endif
NTC3950thermistorActivity::NTC3950thermistorActivity(AvrMicroRepository& avrMicroRepository, AnalogPortC** analogPortForCustomMisure, uint8_t analogPortsNumber, float r1_divider_resistor) :AnalogPortCActivity(avrMicroRepository, analogPortForCustomMisure, analogPortsNumber) {
	divider_resistor = r1_divider_resistor;
}
bool NTC3950thermistorActivity::is_any_port_out_of_range() {
	bool return_value = false;
	uint16_t digital_read;
	for (int i = 0; i < this->get_analog_ports_number(); i++) {
		float T_sum = 0.0;
		/*for (int ii = 0; ii < this->avg_size; ii++) {*/
		digital_read = this->get_analog_ports()[i]->digital_value;
		T_sum = adc_to_celsius(digital_read, 1023, this->get_avr_micro_repository()->get_vref());
		//}
		float T_approx = T_sum;/* / float(avg_size);*/
#if _DEBUG_FOR_SERIAL
		Serial.print("tmp.");Serial.print(i); Serial.print(" : "); Serial.println(T_approx);
#endif
		if (T_approx > this->get_analog_ports()[i]->getMaxUnitOfMisureAlarmValue()) {
#if _DEBUG_FOR_SERIAL
			Serial.print("getMaxUnit:"); Serial.println(this->get_analog_ports()[i]->getMaxUnitOfMisureAlarmValue());
#endif
#if _DEBUG_FOR_SERIAL
			Serial.print("temp above:"); Serial.println(T_approx);
#endif
			this->get_analog_ports()[i]->is_alarm_above_threshold = true;
			this->get_analog_ports()[i]->is_onAlarm = true;
			this->get_analog_ports()[i]->is_time_above_threshold_elapsed = this->is_delay_elapsed_for_ports_above_threshold(this->get_analog_ports()[i]);
			return_value = true;
		}
		else if (T_approx < this->get_analog_ports()[i]->getMinUnitOfMisureAlarmValue()) {
#if _DEBUG_FOR_SERIAL
			Serial.print("temp under:"); Serial.println(T_approx);
#endif
			this->get_analog_ports()[i]->is_alarm_under_threshold = true;
			this->get_analog_ports()[i]->is_onAlarm = true;
			this->get_analog_ports()[i]->is_time_under_threshold_elapsed = this->is_delay_elapsed_for_ports_under_threshold(this->get_analog_ports()[i]);
			return_value = true;
		}
		else {
			this->get_analog_ports()[i]->first_time_on_alarm = 0;
			this->get_analog_ports()[i]->is_time_under_threshold_elapsed = false;
		}
	}
	return return_value;
}
float NTC3950thermistorActivity::adc_to_celsius(uint16_t digital_read, uint16_t max_adc_resolution, float vref) {
	float voltage = vref * (float)digital_read / (float)max_adc_resolution;
	if (voltage <= 0.0f || voltage >= vref) return NAN;               // fuori range
	float ntc_resistor = divider_resistor * voltage / (vref - voltage);
	float invT = (1.0f / ntc_temp25C) + (1.0f / ntc_beta) * logf(ntc_resistor / ntc_r25C);
	float temperature = (1.0f / invT) - 273.15f;
	return temperature;
}

