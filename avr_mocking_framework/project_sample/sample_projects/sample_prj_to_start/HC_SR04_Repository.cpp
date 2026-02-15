#include "HC_SR04_Repository.h"
#include <Arduino.h>
HC_SR04_Repository::HC_SR04_Repository(AvrMicroRepository& avrMicroRepository, uint8_t triggerPin, uint8_t echoPin)
	: avrMicroRepository(&avrMicroRepository), triggerPin(triggerPin), echoPin(echoPin) {
	avrMicroRepository.pinMode(triggerPin, OUTPUT);
	avrMicroRepository.pinMode(echoPin, INPUT);
}
float HC_SR04_Repository::measure_distance_cm(unsigned long time_out) {
	// Genera un impulso di trigger di 10 microsecondi
	avrMicroRepository->digitalWrite(triggerPin, LOW);
	avrMicroRepository->delayMicroseconds(2);
	avrMicroRepository->digitalWrite(triggerPin, HIGH);
	avrMicroRepository->delayMicroseconds(10);
	avrMicroRepository->digitalWrite(triggerPin, LOW);
	// Leggi il tempo di ritorno dell'eco in microsecondi
	unsigned long t_us = avrMicroRepository->pulseIn(echoPin, HIGH, time_out);
	// Calcola la distanza in centimetri (velocità del suono ~ 343 m/s)
	float d_cm = (t_us == 0) ? -1.0f : (t_us / 58.0f);
	return d_cm;
}
