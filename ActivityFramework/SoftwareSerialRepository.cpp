#include "SoftwareSerialRepository.h"
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <avr/pgmspace.h>

SoftwareSerial* _softwareSerial = nullptr;

SoftwareSerialRepository::SoftwareSerialRepository(uint8_t rx, uint8_t tx, unsigned long baud, bool inv_logic = false) {
	this->_rxPin = rx;
	this->_txPin = tx;
	this->invers_logic = inv_logic;
	this->_baud = baud;
	_softwareSerial = new SoftwareSerial(rx, tx, inv_logic);
	begin_m(this->_baud);
}

SoftwareSerialRepository::~SoftwareSerialRepository()
{
		delete(_softwareSerial);
}


/// <summary>
/// return a char* pointer, remember to free memory.
/// </summary>
/// <returns>return a char*</returns>
char* SoftwareSerialRepository::readString_m() {
	String responseBufferString = _softwareSerial->readString();
	char* charsBufferByReference;
	charsBufferByReference = (char*)calloc(responseBufferString.length(), sizeof(char));
	if (charsBufferByReference == nullptr)
	{
		return '\0';
	}
	responseBufferString.toCharArray(charsBufferByReference, responseBufferString.length());
	return charsBufferByReference;
}

void SoftwareSerialRepository::clearBuffer_m()
{
	char buffer[_SS_MAX_RX_BUFF];
	_softwareSerial->readBytes(buffer, _SS_MAX_RX_BUFF);
}

int SoftwareSerialRepository::get_SS_MAX_RX_BUFF()
{
	return _SS_MAX_RX_BUFF;
}


void SoftwareSerialRepository::print_m(const char* data, bool isNewLine = false)
{
	_softwareSerial->print(data);
	if (isNewLine)_softwareSerial->println();
}


int SoftwareSerialRepository::serial_available(){
	return _softwareSerial->available();
}

int SoftwareSerialRepository::read_m() {
		return _softwareSerial->read();
}

void SoftwareSerialRepository::begin_m(unsigned long baud)
{
	_softwareSerial->begin(baud);
}


