#pragma once   
#include <math.h>  
#include <mf_repository_AvrMicroRepository.h>
#include <mf_activity_AnalogPortCActivity.h>
#include <mf_model_AnalogPortC.h>
class NTC3950thermistorActivity : public AnalogPortCActivity {
public:
	NTC3950thermistorActivity(AvrMicroRepository& avrMicroRepository, AnalogPortC** analogPortForCustomMisure, uint8_t analogPortsNumber, float r1_divider_resistor);
	bool  is_any_port_out_of_range() override;
private:
	float adc_to_celsius(uint16_t digital_read, uint16_t max_adc_resolution, float Vref);
	float divider_resistor = 0.00f;
	float ntc_r25C = 100000.00f;
	float ntc_beta = 3950.00f;
	float ntc_temp25C = 298.15f; //Kelvin
	/*int avg_size = 10;*/
};
