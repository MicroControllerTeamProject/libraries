#pragma once
#include "AvrMicroRepository.h"
#include <SoftwareSerial.h>

class SoftwareSerialRepository :public AvrMicroRepository
{
public:
	SoftwareSerialRepository();
	virtual void init(uint8_t rx, uint8_t tx, bool inv_logic);
	virtual void print_m(const char* data);
	virtual void print_m(float data);
	virtual void println(const char* data);
	virtual void println(float data);
	virtual bool serial_available();
	virtual int read();
	char* readString();
	char* readBuffer();
	virtual ~SoftwareSerialRepository();
protected:
	uint8_t _rxPin;
	uint8_t _txPin;
	bool invers_logic;
	SoftwareSerial* softwareSerial = nullptr;
};

