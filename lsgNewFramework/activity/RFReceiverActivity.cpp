#include "RFReceiverActivity.h"
#include <string.h>

RFReceiverActivity::RFReceiverActivity(RFReceiverRepository& rfReceiverRepository)
{
	this->rfReceiverRepository = &rfReceiverRepository;
	this->rfReceiverRepository->begin();
}

uint8_t* RFReceiverActivity::getMessage()
{
	return this->rfReceiverRepository->getMessage();
}

bool RFReceiverActivity::isGotMessage(char message[3]) 
{
	if (strcmp((const char*)this->rfReceiverRepository->getMessage(), message) == 0)
	{
		return true;
	}
	return false;
}



