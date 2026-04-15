#include <mf_repository_HCSR04Repository.h>
#include <Arduino.h>
HC_SR04_Repository::HC_SR04_Repository(uint8_t triggerPin, uint8_t echoPin) {
	this->triggerPin = triggerPin;
	this->echoPin = echoPin;
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);
}
// HC_SR04_Repository.cpp
int16_t HC_SR04_Repository::measure_distance_cm(unsigned long time_out){
	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
	unsigned long t_us = pulseIn(echoPin, HIGH, time_out);
	if (t_us == 0) return -1;                 // timeout / no echo
	// cm ≈ t_us / 58  (arrotondato)
	return (int16_t)((t_us + 29UL) / 58UL);   // +29 per round-to-nearest
}

