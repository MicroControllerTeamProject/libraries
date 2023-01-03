#pragma once
#include "AvrMicroRepository.h"


class UltrasonicRepository :public AvrMicroRepository
{
public:
	UltrasonicRepository();
	virtual unsigned int getDistance(uint8_t triggerPortPin,uint8_t echoPortPin,unsigned long timeout);
private:
protected:
};

