#pragma once
#include <Arduino.h>
class LSG_EEpromRW
{
public:
	LSG_EEpromRW();
	~LSG_EEpromRW();
	boolean eeprom_read_string(int addr, char* buffer, int bufSize);
	boolean eeprom_write_string(int addr, const char* string);
	boolean write_StringEE(int Addr, String input);
};

