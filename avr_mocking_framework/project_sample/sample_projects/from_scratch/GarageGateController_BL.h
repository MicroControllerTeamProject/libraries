#pragma once 
#include <mf_repository_AvrMicroRepository.h>
#include <mf_activity_NTC3950thermistorActivity.h>
#include <mf_activity_HCSR04.h>
class GarageGateController_BL{
public:
	GarageGateController_BL(AvrMicroRepository & avrMicroRepository, 
		NTC3950thermistorActivity ntc3950thermistorActivity,
		HCSR04Activity hcsR04Activity,DigitalPortActivity gate_rele_activity);
	bool GarageGateController_BL::open_the_door();
private:
	AvrMicroRepository & avrMicroRepository;
	NTC3950thermistorActivity ntc3950thermistorActivity;
	HCSR04Activity hcsR04Activity;
	DigitalPortActivity  gate_rele_activity;
};

