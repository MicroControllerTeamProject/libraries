#pragma once
class InterfaceMicroRepository
{
public:
	~InterfaceMicroRepository() {}

	virtual void analogReferencem(uint8_t mode) = 0;

	virtual uint16_t analogReadm(uint8_t analogPin)=0;

	virtual float analogVoltageRead_m(uint8_t analogPin, float _vref, uint8_t mode)=0;

	virtual uint8_t digitalReadm(uint8_t analogPin)=0;

	virtual void pinMode_m(uint8_t pin, uint8_t mode)=0;

	virtual void delaym(unsigned long delayTime)=0;

	virtual int getFreeRam()=0;

	virtual void free_m(void* _ptr)=0;

	virtual void tone_m(unsigned int pin, unsigned int frequency, unsigned long duration = 0UL)=0;

	virtual void notone_m(uint8_t pin)=0;

	virtual void digitalWrite_m(uint8_t analogPin, uint8_t value) = 0;
};

