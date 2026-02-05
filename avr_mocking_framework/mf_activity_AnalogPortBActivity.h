#pragma once
#include <mf_model_AnalogPortB.h>
#include <mf_repository_AvrMicroRepository.h>
#include <stdint.h>
#if _DEBUG_FOR_SERIAL
#include <Arduino.h>
#endif // _DEBUG_FOR_SERIAL

class AnalogPortBActivity{
public:
	AnalogPortBActivity(AvrMicroRepository& avrMicroRepository, uint8_t analogPortsNumber,AnalogPortB** analogPortBase);
	virtual ~AnalogPortBActivity() = 0;
	AvrMicroRepository* get_avr_micro_repository();
	bool is_delay_elapsed_for_ports_under_threshold(AnalogPortB* AnalogPortB);
	bool is_delay_elapsed_for_ports_above_threshold(AnalogPortB* AnalogPortB);
	void analog_read_for_all_ports();
	uint16_t analog_read_average(uint8_t pin,uint8_t index_port, uint8_t number_of_read);
	void set_offset(uint8_t pin, uint8_t index_port, uint8_t number_of_read);
	uint8_t get_analog_ports_number();
	void reset_ports();
	void set_process_status(mf::commons::commonsLayer::ProcessStatus status);
	mf::commons::commonsLayer::ProcessStatus get_process_status();
private:
	uint8_t analog_port_number = 0;
	AvrMicroRepository* avrMicroRepository = nullptr;
	AnalogPortB** analogPortB = {};
	mf::commons::commonsLayer::ProcessStatus processBlokedBy = mf::commons::commonsLayer::ProcessStatus::blocked_level_too_high;
};
inline AnalogPortBActivity::~AnalogPortBActivity() {}

