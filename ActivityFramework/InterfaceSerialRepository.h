#pragma once
class InterfaceSerialRepository
{
public:
	~InterfaceSerialRepository(){}

	virtual void print_m(const char* data, bool isNewLine = false) = 0;

	virtual int serial_available() = 0;

/// <summary>
/// assigne value to a char* pointer, after remeber to free memory.
/// </summary>
/// <returns>return a char*</returns>
	virtual char* readString_m() = 0;


	virtual void clearBuffer_m() = 0;

	virtual void begin_m(unsigned long baud) = 0;

	virtual int read_m() = 0;

	virtual int get_SS_MAX_RX_BUFF() = 0;
};

