#pragma once
#include <stdint.h>
#include "InterfaceSerialRepository.h"

class SoftwareSerialRepository : public InterfaceSerialRepository
{
public:
	SoftwareSerialRepository(uint8_t rx, uint8_t tx, unsigned long baud, bool inv_logic = false);
	virtual ~SoftwareSerialRepository();

	virtual void print_m(const char* data, bool isNewLine = false);

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

