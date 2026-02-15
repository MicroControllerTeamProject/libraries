#pragma once
#include <stdint.h>
#include <mf_repository_AvrMicroRepository.h>
class HC_SR04_Repository {
public:	
	HC_SR04_Repository(AvrMicroRepository& avrMicroRepository, uint8_t triggerPin, uint8_t echoPin);
	virtual float measure_distance_cm(unsigned long time_out);
private:
	AvrMicroRepository* avrMicroRepository;
	uint8_t triggerPin;
	uint8_t echoPin;
};

