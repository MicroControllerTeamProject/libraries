// File: DigitalPort.h
#pragma once
#include <stdint.h>
#include <mf_commons_commonsLayer.h>
// includi un header “pubblico” della libreria framework, non un path relativo
class DigitalPort {
public:
	DigitalPort(char group_id, uint8_t pin, 
        mf::commons::commonsLayer::PortDirection portDirection = mf::commons::commonsLayer::PortDirection::noset,
        mf::commons::commonsLayer::AlarmTriggerOn alarmTriggerOn = mf::commons::commonsLayer::AlarmTriggerOn::noset);
    bool is_enabled = true;
    bool is_onAlarm = false;
	// pin_value is used only for testing purposes, it is not updated by the library, but it can be set from outside for simulating pin state in tests.
    bool pin_value_for_tdd = 0;
    bool is_on_pull_up = false;
    char get_group_id();
    uint8_t get_pin();
    mf::commons::commonsLayer::PortDirection get_port_direction();
    mf::commons::commonsLayer::AlarmTriggerOn get_alarm_trigger_on();
private:
    mf::commons::commonsLayer::PortDirection portDirection = mf::commons::commonsLayer::PortDirection::noset;
    mf::commons::commonsLayer::AlarmTriggerOn alarmTriggerOn = mf::commons::commonsLayer::AlarmTriggerOn::high;
    char group_id = {};
    uint8_t pin = 0;
};
