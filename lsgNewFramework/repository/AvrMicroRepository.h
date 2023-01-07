#pragma once
#include "stdint.h"

class AvrMicroRepository
{
public:

	AvrMicroRepository();

	virtual void analogReferencem(uint8_t mode);

	virtual uint16_t analogReadm(uint8_t analogPin);

	virtual float analogVoltageRead_m(uint8_t analogPin, float _vref, uint8_t mode);

	virtual uint8_t digitalReadm(uint8_t analogPin);

	virtual void print_m(const char* data, bool isNewLine = false);

	virtual void print_m(float data, bool isNewLine = false);

	virtual void print_m(int data, bool isNewLine = false);

	virtual void print_m(uint8_t data, bool isNewLine = false);

	virtual bool serial_available();

	virtual char* readString_m();

	virtual void clearBuffer_m();

	virtual void begin_m(unsigned long baud);

	virtual int read();

	virtual void pinMode_m(uint8_t pin, uint8_t mode);

	virtual void delaym(unsigned long delayTime);

	virtual int getFreeRam();

	virtual void free_m(void* _ptr);

	virtual void tone_m(unsigned int pin,unsigned int frequency,unsigned long duration = 0UL);

	virtual void notone_m(uint8_t pin);
	
private:

protected:
	

};

