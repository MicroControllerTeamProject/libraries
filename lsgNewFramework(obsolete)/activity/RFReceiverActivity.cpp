#include "RFReceiverActivity.h"
#include <string.h>

RFReceiverActivity::RFReceiverActivity(RFReceiverRepository& rfReceiverRepository)
{
	this->rfReceiverRepository = &rfReceiverRepository;
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

void RFReceiverActivity::begin()
{
	this->rfReceiverRepository->begin();
}

void RFReceiverActivity::stop()
{
	this->rfReceiverRepository->stop();
}



