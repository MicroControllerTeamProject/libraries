#include "mf_repository_HCSR04Repository.h"
#include <Arduino.h>
HC_SR04_Repository::HC_SR04_Repository(AvrMicroRepository& avrMicroRepository, uint8_t triggerPin, uint8_t echoPin)
	: avrMicroRepository(&avrMicroRepository), triggerPin(triggerPin), echoPin(echoPin) {
	avrMicroRepository.pinMode(triggerPin, OUTPUT);
	avrMicroRepository.pinMode(echoPin, INPUT);
}
float HC_SR04_Repository::measure_distance_cm(unsigned long time_out) {
	// Genera un impulso di trigger di 10 microsecondi
	this->avrMicroRepository->digitalWrite(triggerPin, LOW);
	this->avrMicroRepository->delayMicroseconds(2);
	this->avrMicroRepository->digitalWrite(triggerPin, HIGH);
	this->avrMicroRepository->delayMicroseconds(10);
	this->avrMicroRepository->digitalWrite(triggerPin, LOW);
	// Leggi il tempo di ritorno dell'eco in microsecondi
	unsigned long t_us = this->avrMicroRepository->pulseIn(echoPin, HIGH, time_out);
	// Calcola la distanza in centimetri (velocità del suono ~ 343 m/s)
	float d_cm = (t_us == 0) ? -1.0f : (t_us / 58.0f);
	return d_cm;
}
