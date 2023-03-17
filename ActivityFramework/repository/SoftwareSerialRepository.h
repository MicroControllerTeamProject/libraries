#pragma once
#include <stdint.h>
#include "../interfaces/InterfaceSerialRepository.h"

class SoftwareSerialRepository : public InterfaceSerialRepository
{
public:
	SoftwareSerialRepository(uint8_t rx, uint8_t tx, unsigned long baud, bool inv_logic = false);
	virtual ~SoftwareSerialRepository();
	/*virtual char* readString_m();
	virtual void print_m(float data);
	virtual void println(const char* data);
	virtual void println(float data);
	virtual bool serial_available();
	virtual int read();
	virtual void begin_m(unsigned long baud);*/
	
	virtual void print_m(const char* data, bool isNewLine = false);

	//virtual void print_m(float data, bool isNewLine = false);

	//virtual void print_m(int data, bool isNewLine = false);

	//virtual void print_m(uint8_t data, bool isNewLine = false);

	virtual int serial_available();

	virtual char* readString_m();

	virtual void clearBuffer_m();

	virtual int get_SS_MAX_RX_BUFF();

	virtual void begin_m(unsigned long baud);

	virtual int read_m();





protected:
	uint8_t _rxPin;
	uint8_t _txPin;
	bool invers_logic;
	unsigned long _baud = 0;
	
};

