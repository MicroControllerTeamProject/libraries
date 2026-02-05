#pragma once
#include <mf_model_AnalogPortD.h>
#include <mf_activity_AnalogPortBActivity.h>
#include <mf_repository_AvrMicroRepository.h>
#include <mf_commons_commonsLayer.h>
class AnalogPortDActivity : public AnalogPortBActivity{
public:
	AnalogPortDActivity(AvrMicroRepository& avrMicroRepository,AnalogPortD** analogPortForDigitalMeasure,uint8_t analogPortsNumber);
	AnalogPortD** get_analog_ports();
	AnalogPortD* get_port_by_pin(uint8_t pin);
	virtual bool AnalogPortDActivity::is_any_port_out_of_range();
private:
	AnalogPortD** analogPortForDigitalMeasure = {};
};

