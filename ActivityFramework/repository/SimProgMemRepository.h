#pragma once
#include <stdint.h>


#include "../interfaces/InterfaceSerialRepository.h"

class SimProgMemRepository
{
public:
	SimProgMemRepository();
	/*virtual void sendAtCommand(uint16_t index, InterfaceSerialRepository* repo);*/
	virtual void getAtCommand(uint16_t index, char* atCommandbuffer, uint8_t atCommandBufferLenght);
	virtual char* getSmsToFind(uint16_t index, char* responseDatabuffer, uint8_t responseDatabufferLenght);
	virtual const uint16_t getProgMemSmsToFindLenght(uint16_t stringIndex);
	virtual const uint16_t getAtCommandIndexLengthString(uint16_t stringIndex);
private:
	virtual const uint16_t getStringLength(const char simCommands[], uint16_t index);
	virtual char* fillStringBuffer(char buffer[], uint16_t length, uint16_t index, const char preogMemString[]);

};

