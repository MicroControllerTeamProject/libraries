#include "AvrMicroRepository.h"
#include <Arduino.h>


//for some MCUs (i.e. the ATmega2560) there's no definition for RAMSTART
#ifndef RAMSTART
extern int __data_start;
#endif

extern int __data_end;
//extern int __bss_start;
//extern int __bss_end;
extern int __heap_start;
extern int __brkval;
int temp;


AvrMicroRepository::AvrMicroRepository(unsigned long baud) {
	this->begin_m(baud);
}

void AvrMicroRepository::analogReferencem(uint8_t mode)
{
	analogReference(mode);
}

uint16_t AvrMicroRepository::analogReadm(uint8_t analogPin) {
	return analogRead(analogPin);
}

float AvrMicroRepository::analogVoltageRead_m(uint8_t analogPin, float _vref, uint8_t mode) {
	analogReference(mode);
	return (_vref / 1024.0f) * analogRead(analogPin);
}

uint8_t AvrMicroRepository::digitalReadm(uint8_t analogPin) {
	return digitalRead(analogPin);
}

void AvrMicroRepository::digitalWrite_m(uint8_t analogPin, uint8_t value)
{
	 digitalWrite(analogPin,value);
}

void AvrMicroRepository::print_m(const char* data,bool isNewLine = false)
{
#if defined(__AVR_ATmega328P__)
	Serial.print(data);
	if (isNewLine)Serial.println();
#endif
}

void AvrMicroRepository::print_m(float data, bool isNewLine = false)
{
#if defined(__AVR_ATmega328P__)
	Serial.print(data);
	if (isNewLine)Serial.println();
#endif
}


void AvrMicroRepository::print_m(int data, bool isNewLine = false)
{
#if defined(__AVR_ATmega328P__)
	Serial.print(data);
	if (isNewLine)Serial.println();
#endif
}

void AvrMicroRepository::print_m(uint8_t data, bool isNewLine)
{
#if defined(__AVR_ATmega328P__)
	Serial.print(data);
	if (isNewLine)Serial.println();
#endif
}

//void AvrMicroRepository::println(const char* data)
//{
//	Serial.println(data);
//	delay(100);
//}
//
//void AvrMicroRepository::println(float data)
//{
//	Serial.println(data);
//	delay(100);
//}

int AvrMicroRepository::serial_available()
{
#if defined(__AVR_ATmega328P__)
	return Serial.available();
#endif
}

void AvrMicroRepository::begin_m(unsigned long baud)
{
#if defined(__AVR_ATmega328P__)
	Serial.begin(baud);
#endif
}

int AvrMicroRepository::read_m() {
#if defined(__AVR_ATmega328P__)
	return Serial.read();
#endif

}

//return value need to free() memory.
char* AvrMicroRepository::readString_m() {
#if defined(__AVR_ATmega328P__)
	String responseBufferString = "";// = Serial.readString();
		while (Serial.available() > 0) {
			responseBufferString.concat((char)Serial.read());
		}
	char* charsBufferByReference;
	charsBufferByReference = (char*)calloc(responseBufferString.length(), sizeof(char));
	if (charsBufferByReference == nullptr)
	{
#if defined(__AVR_ATmega328P__)
#ifdef _DEBUG
		Serial.println("nP");
#endif
#endif
		return '\0';
	}
	responseBufferString.toCharArray(charsBufferByReference, responseBufferString.length());
	return charsBufferByReference;
#endif
}


//void AvrMicroRepository::clearBuffer_m() {
//	delay(100);
//	while (Serial.available() > 0) {
//		Serial.readString();
//	}
//	Serial.readString();
//}

void AvrMicroRepository::pinMode_m(uint8_t pin, uint8_t mode)
{
	pinMode(pin, mode);
}

void AvrMicroRepository::delaym(unsigned long delayTime)
{
	delay(delayTime);
}

int AvrMicroRepository::getFreeRam() {
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void  AvrMicroRepository::free_m(void* _ptr)
{
	free(_ptr);
}

void AvrMicroRepository::tone_m(unsigned int pin, unsigned int frequency, unsigned long duration)
{
	tone(pin, frequency, duration);
}

void AvrMicroRepository::notone_m(uint8_t pin)
{
	noTone(pin);
}

void AvrMicroRepository::clearBuffer_m()
{
#if defined(__AVR_ATmega328P__)
	char buffer[SERIAL_RX_BUFFER_SIZE];
	Serial.readBytes(buffer, SERIAL_RX_BUFFER_SIZE);
#endif
	/*while () {
		_softwareSerial->readString();
	}
	_softwareSerial->readString();*/
	/*while (_softwareSerial->available() > 0) {
		_softwareSerial->readString();
	}
	_softwareSerial->readString();*/
}

int AvrMicroRepository::get_SS_MAX_RX_BUFF()
{
	return SERIAL_RX_BUFFER_SIZE;
}






