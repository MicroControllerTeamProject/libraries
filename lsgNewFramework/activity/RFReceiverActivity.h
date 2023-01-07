#pragma once
#include "..\repository\RFReceiverRepository.h"
class RFReceiverActivity
{
public:
	RFReceiverActivity(RFReceiverRepository& RFReceiverRepository);
	uint8_t* getMessage();
	bool isGotMessage(char message[3]);
	void begin();
	void stop();
protected:
	RFReceiverRepository* rfReceiverRepository = nullptr;
};

