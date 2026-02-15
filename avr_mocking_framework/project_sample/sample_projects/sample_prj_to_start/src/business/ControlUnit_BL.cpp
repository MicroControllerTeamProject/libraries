
#include "ControlUnit_BL.h"
#include <mf_commons_commonsLayer.h>
#include <mf_activity_NTC3950thermistorActivity.h>
#if _DEBUG_FOR_SERIAL
#include <Arduino.h>
#endif // _DEBUG_FOR_SERIAL
#define HIGH 1
#define LOW 0
ControlUnit_BL::ControlUnit_BL(AvrMicroRepository& avrMicroRepository, 
	NTC3950thermistorActivity& thermistorActivity,DigitalPortActivity& relayActivity, AnalogPortCActivity& currentActivity)
	: avrMicroRepository(avrMicroRepository), thermistorActivity(thermistorActivity), 
	relayActivity(relayActivity), currentActivity(currentActivity) {
	this->avrMicroRepository.pinMode(AppConfig::reset_counter_pin, (bool)mf::commons::commonsLayer::PortDirection::output);
	this->avrMicroRepository.pinMode(AppConfig::ckl_counter_pin, (bool)mf::commons::commonsLayer::PortDirection::output);
	this->avrMicroRepository.pinMode(AppConfig::enable_demux_relay_pin, (bool)mf::commons::commonsLayer::PortDirection::output);
	this->avrMicroRepository.pinMode(AppConfig::demux_sensors_signal_pin, (bool)mf::commons::commonsLayer::PortDirection::output);
}
ControlUnit_BL::~ControlUnit_BL() {}
void ControlUnit_BL::reset_counter() {
	this->avrMicroRepository.digitalWrite(AppConfig::reset_counter_pin, HIGH); // Reset del contatore
	this->avrMicroRepository.delay(10); // Attesa di 10 ms
	this->avrMicroRepository.digitalWrite(AppConfig::reset_counter_pin, LOW); // Fine del reset
#if _ON_MOCKING_TESTS
	this->demux_plexer_status.selected_chanell = 0; // Resetta il canale selezionato nel demux (solo per test)
#endif // _on_mocking_tests
}
void ControlUnit_BL::set_position_counter(uint8_t position) {
	for (uint8_t i = 0; i < position; i++) {
		this->avrMicroRepository.digitalWrite(AppConfig::ckl_counter_pin, HIGH); // Imposta il pin del contatore a HIGH
		this->avrMicroRepository.delay(10); // Attesa di 10 ms
		this->avrMicroRepository.digitalWrite(AppConfig::ckl_counter_pin, LOW); // Imposta il pin del contatore a LOW
		this->avrMicroRepository.delay(10); // Attesa di 10 ms
#if _ON_MOCKING_TESTS
		this->demux_plexer_status.selected_chanell++;
#endif // _on_mocking_tests
	}
}
void ControlUnit_BL::enable_demux_sensors() {
	this->avrMicroRepository.digitalWrite(AppConfig::enable_demux_relay_pin, LOW);
#if _ON_MOCKING_TESTS
	this->demux_plexer_status.en_status = false;
#endif // _on_mocking_tests
}
void ControlUnit_BL::disable_demux_sensors() {
	this->avrMicroRepository.digitalWrite(AppConfig::enable_demux_relay_pin, HIGH);
#if _ON_MOCKING_TESTS
	this->demux_plexer_status.en_status = true;
#endif // _on_mocking_tests
}
bool ControlUnit_BL::is_current_port_values_out_of_range() {
	uint8_t ports_number = this->currentActivity.get_analog_ports_number();
	for (uint8_t i = 0; i < ports_number; i++) {
		disable_demux_sensors();
		reset_counter();
		set_position_counter(this->currentActivity.get_analog_ports()[i]->get_pin());
		enable_demux_sensors();
#ifndef _ON_MOCKING_TESTS
		uint8_t number_of_read = 10;
#else
		uint8_t number_of_read = 1;
#endif // _ON_MOCKING_TESTS
		this->currentActivity.analog_read_average(AppConfig::demux_sensors_signal_pin, i, number_of_read);
#if _DEBUG_FOR_SERIAL
		Serial.print("Cur."); Serial.print(i); Serial.print(" : "); Serial.println(this->currentActivity.get_analog_ports()[i]->digital_value);
#endif // 

	}
	return this->currentActivity.is_any_port_out_of_range();
}
bool ControlUnit_BL::is_thermistor_port_values_out_of_range() {
	//bool is_first_read = true;
	uint8_t ports_number = this->thermistorActivity.get_analog_ports_number();
	for (uint8_t i = 0; i < ports_number; i++) {
		disable_demux_sensors();
		reset_counter();
		set_position_counter(this->thermistorActivity.get_analog_ports()[i]->get_pin());
		enable_demux_sensors();
		/*if (is_first_read) {
			enable_demux_sensors();
			this->avrMicroRepository.delay(500);
			is_first_read = false;
		}*/
		this->thermistorActivity.analog_read_average(AppConfig::demux_sensors_signal_pin, i, 10);
	}
	return this->thermistorActivity.is_any_port_out_of_range();
}
bool ControlUnit_BL::disable_relays_where_current_is_on_alarm() {
	bool return_value = false;
	if (is_current_port_values_out_of_range()) {
		return_value = true;
		for (uint8_t i = 0; i < this->currentActivity.get_analog_ports_number(); i++) {
			if (this->currentActivity.get_analog_ports()[i]->is_onAlarm &&
				(this->currentActivity.get_analog_ports()[i]->is_time_above_threshold_elapsed ||
					this->currentActivity.get_analog_ports()[i]->is_time_under_threshold_elapsed)) {
				turn_off_relay_by_group(this->currentActivity.get_analog_ports()[i]->get_group_id());
			}
		}
	}
	return return_value;
}
bool ControlUnit_BL::disable_relays_where_thermistor_is_on_alarm() {
	bool return_value = false;
	if (is_thermistor_port_values_out_of_range()) {
		return_value = true;
		for (uint8_t i = 0; i < this->thermistorActivity.get_analog_ports_number(); i++) {
			if (this->thermistorActivity.get_analog_ports()[i]->is_onAlarm &&
				this->thermistorActivity.get_analog_ports()[i]->is_time_above_threshold_elapsed ||
					this->thermistorActivity.get_analog_ports()[i]->is_time_under_threshold_elapsed) {
				turn_off_relay_by_group(this->thermistorActivity.get_analog_ports()[i]->get_group_id());
				//used for avoid reading spikes
				this->avrMicroRepository.delay(500);
			}
		}
	}
	return return_value;
}
void ControlUnit_BL::turn_on_off_all_relays(bool turn_on) {
	uint8_t np = this->relayActivity.get_ports_number();
	for (size_t i = 0; i < np; i++) {
		this->avrMicroRepository.digitalWrite(this->relayActivity.get_digital_ports()[i]->get_pin(), turn_on);
#ifdef _ON_MOCKING_TESTS
		this->relayActivity.get_digital_ports()[i]->pin_value_for_tdd = turn_on;
#endif // 
	}
}
bool ControlUnit_BL::turn_off_relay_by_group(char group_id) {
	bool return_value = false;
	uint8_t np = this->relayActivity.get_ports_number();
	for (size_t i = 0; i < np; i++) {
		if (this->relayActivity.get_digital_ports()[i]->get_group_id() == group_id && this->relayActivity.get_digital_ports()[i]->pin_value_for_tdd == true) {
			this->avrMicroRepository.digitalWrite(this->relayActivity.get_digital_ports()[i]->get_pin(), false);
#ifdef _ON_MOCKING_TESTS
			this->relayActivity.get_digital_ports()[i]->pin_value_for_tdd = false;
#endif // 
			return_value = true;
		}
	}
	return return_value;
}
void ControlUnit_BL::calculate_current_sensors_offset(uint8_t number_of_read) {
	uint8_t ports_number = this->currentActivity.get_analog_ports_number();
	for (uint8_t i = 0; i < ports_number; i++) {
		disable_demux_sensors();
		reset_counter();
		set_position_counter(this->currentActivity.get_analog_ports()[i]->get_pin());
		enable_demux_sensors();
		this->currentActivity.set_offset(AppConfig::demux_sensors_signal_pin, i, number_of_read);
	}
}
















