#pragma once
#include <mf_model_DigitalPort.h>
DigitalPort::DigitalPort(char group_id,
	uint8_t pin, mf::commons::commonsLayer::PortDirection portDirection,mf::commons::commonsLayer::AlarmTriggerOn alarmTriggerOn) {
	this->pin = pin;
	this->group_id = group_id;
	this->alarmTriggerOn = alarmTriggerOn;
	this->portDirection = portDirection;
}
char DigitalPort::get_group_id() {
	return this->group_id;
}
uint8_t DigitalPort::get_pin() {
	return pin;
}
mf::commons::commonsLayer::AlarmTriggerOn DigitalPort::get_alarm_trigger_on() {
	return this->alarmTriggerOn;
}
mf::commons::commonsLayer::PortDirection DigitalPort::get_port_direction() {
	return this->portDirection;
}


