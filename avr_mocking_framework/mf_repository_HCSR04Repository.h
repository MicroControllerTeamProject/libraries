#pragma once
#include <stdint.h>
class HC_SR04_Repository {
public:	
	HC_SR04_Repository(uint8_t triggerPin, uint8_t echoPin);
	virtual int16_t HC_SR04_Repository::measure_distance_cm(unsigned long time_out);
private:
	uint8_t triggerPin;
	uint8_t echoPin;
};

