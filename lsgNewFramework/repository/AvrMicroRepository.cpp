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


AvrMicroRepository::AvrMicroRepository() {
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
	return (_vref / 1023.0f) * analogRead(analogPin);
}

uint8_t AvrMicroRepository::digitalReadm(uint8_t analogPin) {
	return digitalRead(analogPin);
}

void AvrMicroRepository::print_m(const char* data,bool isNewLine = false)
{
	Serial.print(data);
	if (isNewLine)Serial.println();
	delay(100);
}

void AvrMicroRepository::print_m(float data, bool isNewLine = false)
{
	Serial.print(data);
	if (isNewLine)Serial.println();
	delay(100);
}


void AvrMicroRepository::print_m(int data, bool isNewLine = false)
{
	Serial.print(data);
	if (isNewLine)Serial.println();
	delay(100);
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

bool AvrMicroRepository::serial_available()
{
	if (Serial.available() > 0) return true;
	return false;
}

void AvrMicroRepository::begin_m(unsigned long baud)
{
	Serial.begin(baud);
}

int AvrMicroRepository::read() {
	return Serial.read();
}

////Send a char* empty by reference to fill with Serial.readstring() to avoid to declare a fix array.
//int AvrMicroRepository::readString_m(char* &charsBufferByReference) {
//	String responseBufferString = Serial.readString();
//	/*if (responseBufferString.lastIndexOf("ERROR") != -1)
//	{
//		this->_lastErrorCode = 'E';
//	}*/
//	charsBufferByReference = (char*)calloc(responseBufferString.length(), sizeof(char));
//	responseBufferString.toCharArray(charsBufferByReference, responseBufferString.length());
//	return (int)charsBufferByReference;
//}


//return value need to free() memory.
char* AvrMicroRepository::readString_m() {
	String responseBufferString = Serial.readString();
	char* charsBufferByReference;
	charsBufferByReference = (char*)calloc(responseBufferString.length(), sizeof(char));
	responseBufferString.toCharArray(charsBufferByReference, responseBufferString.length());
	return charsBufferByReference;
}

void AvrMicroRepository::clearBuffer_m() {
	delay(100);
	while (Serial.available() > 0) {
		Serial.readString();
	}
}

void AvrMicroRepository::pinMode_m(uint8_t pin, uint8_t mode)
{
	pinMode(pin, mode);
}

void AvrMicroRepository::delaym(unsigned long delayTime)
{
	delay(delayTime);
}

//char AvrMicroRepository::getLastErrorCode()
//{
//	return this->_lastErrorCode;
//}
//
//void AvrMicroRepository::setLastErrorCode(char errorCode){
//	this->_lastErrorCode = errorCode;
//}


int AvrMicroRepository::getFreeRam() {
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void  AvrMicroRepository::free_m(void* _ptr)
{
	free(_ptr);
}



//void sensor::setLastComunication(char* lastComunication)
//{
//	char message[100];   // array to hold the result.
//	/*char* message2;*/
//	strcpy(message, uid()); // copy string one into the result.
//	strcat(message, " "); // append string two to the result.
//	strcat(message, lastComunication);
//	/*message2 = message;*/
//	_lastComunication = message;
//
//
//}
//
//char* sensor::getLastComunication()
//{
//	return _lastComunication;
//}

//float sensor::getSegnalValue()
//{
//	_sensorValue = analogicRead();
//	return _sensorValue;
//}

//float sensor::analogicRead()
//{
//	_sensorValue = (_vref / 1024) * analogRead(_analSignalPin);
//	return _sensorValue;
//}

//bool sensor::isAnalogicValueOutOfRange()
//{
//	if (analogicRead() >= _maxValue || analogicRead() <= _analogicAllarmMinValue)
//	{
//		setLastComunication("could be damaged");
//		return true;
//	}
//	else
//	{
//		setLastComunication("seems ok");
//		return false;
//	}
//}





