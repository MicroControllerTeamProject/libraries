#pragma once
#include "stdint.h"
#include "InterfaceSerialRepository.h"


class AvrMicroRepository : public InterfaceSerialRepository
{
public:

	AvrMicroRepository(unsigned long baud);

	virtual void analogReferencem(uint8_t mode);

	virtual uint16_t analogReadm(uint8_t analogPin);

	virtual float analogVoltageRead_m(uint8_t analogPin, float _vref, uint8_t mode);

	virtual uint8_t digitalReadm(uint8_t analogPin);

	virtual void digitalWrite_m(uint8_t analogPin,uint8_t value);

	virtual void pinMode_m(uint8_t pin, uint8_t mode);

	virtual void delaym(unsigned long delayTime);

	virtual int getFreeRam();

	virtual void free_m(void* _ptr);

	virtual void tone_m(unsigned int pin, unsigned int frequency, unsigned long duration = 0UL);

	virtual void notone_m(uint8_t pin);



#pragma region SERIALZONE -------------------------------------------

	virtual void print_m(const char* data, bool isNewLine = false);

	virtual void print_m(float data, bool isNewLine = false);

	virtual void print_m(int data, bool isNewLine = false);

	virtual void print_m(uint8_t data, bool isNewLine = false);

	virtual int serial_available();

	virtual char* readString_m();

	virtual void clearBuffer_m();

	virtual int get_SS_MAX_RX_BUFF();

	virtual void begin_m(unsigned long baud);

	virtual int read_m();

#pragma endregion InterfaceSerialRepository -------------------------------------------------

	
	
private:

protected:
	

};

