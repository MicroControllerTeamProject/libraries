
#include <mf_activity_AnalogPortBActivity.h>
AnalogPortBActivity::AnalogPortBActivity(AvrMicroRepository& avrMicroRepository, uint8_t analogPortsNumber, AnalogPortB** analogPortBase) {
	this->avrMicroRepository = &avrMicroRepository; 
	this->analog_port_number = analogPortsNumber;
	this->analogPortB = analogPortBase;
	this->reset_ports();
}
void AnalogPortBActivity::reset_ports() {
	for (int i = 0; i < this->analog_port_number; i++) {
		this->analogPortB[i]->is_onAlarm = false;
		this->analogPortB[i]->is_alarm_above_threshold = false;
		this->analogPortB[i]->is_alarm_under_threshold = false;
		this->analogPortB[i]->first_time_on_alarm = 0;
		this->analogPortB[i]->is_time_under_threshold_elapsed = false;
		this->analogPortB[i]->is_time_above_threshold_elapsed = false;
		this->analogPortB[i]->offset = 0;
	}
}
void AnalogPortBActivity::analog_read_for_all_ports(){
	for (int i = 0; i < this->analog_port_number; i++) {
		this->analogPortB[i]->is_onAlarm = false;
		this->analogPortB[i]->is_alarm_above_threshold = false;
		this->analogPortB[i]->is_alarm_under_threshold = false;
		this->analogPortB[i]->digital_value = this->avrMicroRepository->analogRead(this->analogPortB[i]->get_pin());
		}
}
uint16_t  AnalogPortBActivity::analog_read_average(uint8_t pin, uint8_t index_port,uint8_t number_of_read) {
	//Remove first read spike
#ifndef _ON_MOCKING_TESTS 
	this->avrMicroRepository->analogRead(pin);
	this->avrMicroRepository->delay(100);
#endif // _ON_MOCKING_TESTS
	uint16_t acc = 0;
	for (uint8_t k = 0; k < number_of_read; k++) {
		acc += this->avrMicroRepository->analogRead(pin);
		this->avrMicroRepository->delay(50);
	}
	uint16_t digital_value = (acc / number_of_read) - this->analogPortB[index_port]->offset;
	if (digital_value > 0 && digital_value < 1024) { 
		this->analogPortB[index_port]->digital_value = digital_value; 
	}
	else{
		this->analogPortB[index_port]->digital_value = 0;
	}
	return this->analogPortB[index_port]->digital_value;
}
void  AnalogPortBActivity::set_offset(uint8_t pin, uint8_t index_port, uint8_t number_of_read) {
	this->analogPortB[index_port]->offset = analog_read_average(pin, index_port, number_of_read);
}
bool AnalogPortBActivity::is_delay_elapsed_for_ports_above_threshold(AnalogPortB* AnalogPortB) {
	if (AnalogPortB->is_onAlarm && AnalogPortB->is_alarm_above_threshold) {
		if (AnalogPortB->first_time_on_alarm == 0) {
			AnalogPortB->first_time_on_alarm = this->avrMicroRepository->get_millis();
		}
		else {
			if ((this->avrMicroRepository->get_millis() - AnalogPortB->first_time_on_alarm) >= (AnalogPortB->set_alarm_if_above_threshold_for_seconds * 1000)) {
				return true;
			}
		}
	}
	else {
		AnalogPortB->first_time_on_alarm = 0;
	}
	return false;
}
bool AnalogPortBActivity::is_delay_elapsed_for_ports_under_threshold(AnalogPortB* AnalogPortB) {
	if (AnalogPortB->is_onAlarm && AnalogPortB->is_alarm_under_threshold) {
		if (AnalogPortB->first_time_on_alarm == 0) {
			AnalogPortB->first_time_on_alarm = this->avrMicroRepository->get_millis();
		}else {
			if ((this->avrMicroRepository->get_millis() - AnalogPortB->first_time_on_alarm) >= (AnalogPortB->set_alarm_if_under_threshold_for_seconds * 1000)) {
				return true;
			}
		}
	}else {
		AnalogPortB->first_time_on_alarm = 0;
	}
	return false;
}
uint8_t AnalogPortBActivity::get_analog_ports_number() {
	return this->analog_port_number;
}
AvrMicroRepository* AnalogPortBActivity::get_avr_micro_repository() { 
	return this->avrMicroRepository; };
void AnalogPortBActivity::set_process_status(mf::commons::commonsLayer::ProcessStatus status) {
	this->processBlockedBy = status;
}
mf::commons::commonsLayer::ProcessStatus AnalogPortBActivity::get_process_status() {
	return this->processBlockedBy;
}
