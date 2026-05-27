#include <mf_activity_DigitalPortActivity.h>
DigitalPortActivity::DigitalPortActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** digitalPort, uint8_t digitalPortsNumber) {
	this->avrMicroRepository = &avrMicroRepository;
	this->digitalPort = digitalPort;
	this->digital_port_number = digitalPortsNumber;
	set_ports_direction();
}
DigitalPortActivity::DigitalPortActivity() {}
bool DigitalPortActivity::is_any_port_triggered() {
	bool isOnAlarm = false;
	for (int i = 0; i < this->digital_port_number; i++) {
		if (this->digitalPort[i]->get_port_direction() == mf::commons::commonsLayer::PortDirection::input) {
			if ((this->digitalPort[i]->get_alarm_trigger_on() == mf::commons::commonsLayer::AlarmTriggerOn::high && this->avrMicroRepository->digitalRead(this->digitalPort[i]->get_pin()) == true)
				||
				(this->digitalPort[i]->get_alarm_trigger_on() == mf::commons::commonsLayer::AlarmTriggerOn::low && this->avrMicroRepository->digitalRead(this->digitalPort[i]->get_pin()) == false)) {
#ifdef _ON_MOCKING_TESTS
				this->digitalPort[i]->pin_value_for_tdd = (bool)this->digitalPort[i]->get_alarm_trigger_on();
#endif // 
				this->digitalPort[i]->is_onAlarm = true;
				isOnAlarm = true;
			}
		}
	}
	return isOnAlarm;
}
uint8_t DigitalPortActivity::get_ports_number() {
	return this->digital_port_number;
}
void DigitalPortActivity::turn_port_level(uint8_t pin, bool level) {
	for (int i = 0; i < this->digital_port_number; i++) {
		if (this->digitalPort[i]->get_port_direction() == mf::commons::commonsLayer::PortDirection::output) {
			if (this->digitalPort[i]->get_pin() == pin) {
				this->avrMicroRepository->digitalWrite(digitalPort[i]->get_pin(), level);
#ifdef _ON_MOCKING_TESTS
				this->digitalPort[i]->pin_value_for_tdd = level;
#endif // 
				this->digitalPort[i]->pin_value_for_tdd = level;
				return;
			}
		}
	}
}
DigitalPort* DigitalPortActivity::get_port_by_pin(uint8_t pin) {
	for (int i = 0; i < this->digital_port_number; i++) {
		if (this->digitalPort[i]->get_pin() == pin) {
			return this->digitalPort[i];
		}
	}
}
void DigitalPortActivity::set_ports_direction() {
	for (int i = 0; i < this->digital_port_number; i++) {
		if (this->digitalPort[i]->get_port_direction() != mf::commons::commonsLayer::PortDirection::noset) {
			this->avrMicroRepository->pinMode(this->digitalPort[i]->get_pin(), (uint8_t)this->digitalPort[i]->get_port_direction());
		}
	}
}
