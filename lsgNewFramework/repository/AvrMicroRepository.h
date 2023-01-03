#pragma once
#include "stdint.h"

class AvrMicroRepository
{
public:

	AvrMicroRepository();

	/*~AvrMicroRepository();*/

	virtual void analogReferencem(uint8_t mode);

	virtual uint16_t analogReadm(uint8_t analogPin);

	virtual float analogVoltageRead_m(uint8_t analogPin, float _vref, uint8_t mode);

	virtual uint8_t digitalReadm(uint8_t analogPin);

	/*virtual float analogVrefRead(float vref,uint8_t analogPin);*/

	virtual void print_m(const char* data, bool isNewLine = false);

	virtual void print_m(float data, bool isNewLine = false);

	virtual void print_m(int data, bool isNewLine = false);

	//virtual void println(const char* data);
	//virtual void println(float data);

	virtual bool serial_available();

	virtual char* readString_m();

	virtual void clearBuffer_m();

	virtual void begin_m(unsigned long baud);

	virtual int read();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="charsBufferByReference">char* buffer by reference</param>
	/// <returns>return the charBuffer address memory(use with free((char*)return value)</returns>
	/*virtual int readString_m(char*& charsBufferByReference);*/

	virtual void pinMode_m(uint8_t pin, uint8_t mode);

	virtual void delaym(unsigned long delayTime);

	//virtual char getLastErrorCode();

	//virtual void setLastErrorCode(char errorCode);

	virtual int getFreeRam();

	virtual void free_m(void* _ptr);
	
private:
	/*float _vref;
	uint8_t _referenceMode;*/
protected:
	//char _lastErrorCode = 'X';
	
	
};

