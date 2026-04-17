#pragma once
#include <mf_model_AnalogPortC.h>
#include <mf_repository_AvrMicroRepository.h>
#include <mf_activity_AnalogPortBActivity.h>
class AnalogPortCActivity : public AnalogPortBActivity{
public:
	AnalogPortCActivity(AvrMicroRepository& avrMicroRepository,AnalogPortC** analogPortForCustomMisure,uint8_t analogPortsNumber);
	virtual bool is_any_port_out_of_range();
	float get_unit_of_misure_value_by_index(uint8_t index);
	AnalogPortC** get_analog_ports();
	AnalogPortC* get_port_by_pin(uint8_t pin);
private:
	AnalogPortC** analogPortForCustomMisure = {};
};

