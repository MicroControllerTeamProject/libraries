#include <mf_repository_AvrMicroRepository.h>
#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
// --- Istanza SoftwareSerial confinata al file ---
//SoftwareSerial* softSerial = nullptr;
// --- RAM ---
#ifndef RAMSTART
extern int __data_start;
#endif
extern int __data_end;
extern int __heap_start;
extern int __brkval;
int temp;
#if defined(__has_include)
#if __has_include(<IRremote.hpp>) || __has_include(<IRremote.h>) \
   || __has_include(<IrReceiver.hpp>) || __has_include(<TinyIRReceiver.hpp>)
#define HAS_IRREMOTE 1
#endif
#endif
// --- Costruttore ---
AvrMicroRepository::AvrMicroRepository(ISerial& serial, mf::commons::commonsLayer::AnalogRefMode vref_mode, float vref)
	: serial_(serial)          // inizializzo la reference
	, vref_mode(vref_mode)
	, vref(vref) {
	this->analogReference((uint8_t)vref_mode);
}

AvrMicroRepository::~AvrMicroRepository() {
}

// --- Funzioni analogiche ---
void AvrMicroRepository::analogReference(uint8_t mode) {
	::analogReference(mode);
}
uint16_t AvrMicroRepository::analogRead(uint8_t analogPin) {
	return ::analogRead(analogPin);
}
float AvrMicroRepository::analogVoltageRead(uint8_t analogPin) {
	uint16_t raw = ::analogRead(analogPin);
	return (this->vref / 1024.0f) * raw;
}
// --- Funzioni digitali ---
uint8_t AvrMicroRepository::digitalRead(uint8_t pin) {
	return ::digitalRead(pin);
}
void AvrMicroRepository::digitalWrite(uint8_t pin, uint8_t value) {
	::digitalWrite(pin, value);
}
void AvrMicroRepository::pinMode(uint8_t pin, uint8_t mode) {
	::pinMode(pin, mode);
}
// --- Timing e memoria ---
void AvrMicroRepository::delay(unsigned long delayTime) {
	::delay(delayTime);
}
unsigned long AvrMicroRepository::pulseIn(uint8_t pin,uint8_t level ,unsigned long time = 1000000UL) {
	return pulseIn(pin,level,time);
}
void AvrMicroRepository::delayMicroseconds(unsigned int micSec) {
	::delayMicroseconds(micSec);
	pulseIn(0, 0, 1); // workaround per bug di delayMicroseconds() su AVR (
}
int AvrMicroRepository::getFreeRam() {
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
void AvrMicroRepository::free(void* ptr) {
	::free(ptr);
}
// --- Suoni ---
// #ifndef HAS_IRREMOTE
// void AvrMicroRepository::tone(unsigned int pin, unsigned int frequency, unsigned long duration) {
// 	::tone(pin, frequency, duration);
// }
// #endif
// #ifndef HAS_IRREMOTE
// void AvrMicroRepository::noTone(uint8_t pin) {
// 	::noTone(pin);
// }
// #endif
// --- Stampa seriale ---
void AvrMicroRepository::print(const char* data) {
		serial_.print(data);
}
void AvrMicroRepository::print(float data) {
	serial_.print(data);
}
void AvrMicroRepository::print(int32_t data) {
	serial_.print(data);
}
void AvrMicroRepository::print(uint8_t data) {
	serial_.print(data);
}
void AvrMicroRepository::print(char data) {
	serial_.print(data);
}
void AvrMicroRepository::println(const char* data) {
	serial_.println(data);
}
void AvrMicroRepository::println(float data) {
	serial_.println(data);
}
void AvrMicroRepository::println(int32_t data) {
	serial_.println(data);
}
void AvrMicroRepository::println(uint8_t data) {
	serial_.println(data);
}
void AvrMicroRepository::println(char data) {
	serial_.println(data);
}
// --- Lettura seriale ---
int AvrMicroRepository::available() {
	return serial_.available();
}
size_t AvrMicroRepository::readString(char* buffer, size_t maxLen) {
	size_t i = 0;
	while (serial_.available() && i + 1 < maxLen) {
		buffer[i++] = (char)serial_.read();
	}
	buffer[i] = '\0';
	return i;
}
void AvrMicroRepository::clearBuffer() {
	unsigned long start = millis();
	while (millis() - start < 100) {
		while (serial_.available() > 0) {
			serial_.read();
			start = millis(); // resetta il timeout ogni volta che legge
		}
	}
}
int AvrMicroRepository::getSerialBufferSize() {
	serial_.getRxBufferSize();
}
void AvrMicroRepository::begin(unsigned long baud) {
		serial_.begin(baud);
}
int AvrMicroRepository::read() {
		return serial_.read();
}
// --- SoftwareSerial control ---
unsigned long AvrMicroRepository::get_millis() {
	return millis();
}
float AvrMicroRepository::get_vref() {
	return this->vref;
}
