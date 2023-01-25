#include "UltrasonicActivity.h"
#include <string.h>


//Send two DigitalPort objects,one with the uid equal to parameter triggerPortName,and second with uid equal to echoPortName. 
UltrasonicActivity::UltrasonicActivity(DigitalPort** digitalPort, 
	uint8_t digitalPortsNumber,
	char* triggerPortName,
	char* echoPortName,
	unsigned long timeOut
) : DeviceActivity(digitalPort, digitalPortsNumber)
{
	this->digitalPort = digitalPort;
	this->digitalPortsNumber = digitalPortsNumber;
	this->triggerPortName = triggerPortName;
	this->echoPortName = echoPortName;
	this->timeOut = timeOut;
}

//unsigned int UltrasonicActivity::getDistance(String triggerPortName,String echoPortName)
//{
//	Ultrasonic* ultrasonic;
//
//	uint8_t triggerPortPin;
//
//	uint8_t echoPortPin;
//
//	for (int i = 0; i < this->digitalPortsNumber; i++)
//	{
//		if (this->digitalPort[i]->uid == "triggerPortName")
//		{
//			triggerPortPin = this->digitalPort[i]->pin;
//		}
//
//		if (this->digitalPort[i]->uid == "echoPortName")
//		{
//			echoPortPin = this->digitalPort[i]->pin;
//		}
//	}
//	if (triggerPortPin != NULL && echoPortPin != NULL)
//	{
//		ultrasonic = new Ultrasonic(triggerPortPin, echoPortPin);
//		return ultrasonic->distanceRead();
//	}
//}
unsigned int UltrasonicActivity::getDistance(UltrasonicRepository& ultrasonicRepository) {
	uint8_t triggerPortPin = 0;

	uint8_t echoPortPin = 0;

	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		//if (strcmp(this->digitalPort[i]->getUid(), this->triggerPortName))// && this->digitalPort[i]->direction == DigitalPort::input)
		if ((strcmp(this->digitalPort[i]->getUid(), this->triggerPortName) == 0) && this->digitalPort[i]->direction == DigitalPort::input)
		{
			triggerPortPin = this->digitalPort[i]->getPin();
		}

		if ((strcmp(this->digitalPort[i]->getUid(), this->echoPortName) == 0) && this->digitalPort[i]->direction == DigitalPort::output)
		{
			echoPortPin = this->digitalPort[i]->getPin();
		}
	}
	if (triggerPortPin != NULL && echoPortPin != NULL)
	{
		return ultrasonicRepository.getDistance(triggerPortPin, echoPortPin,this->timeOut);
	}
}

//float UltrasonicActivity::getUnitOfMisureValue(UltrasonicRepository& ultrasonicRepository)
//{
//	uint8_t triggerPortPin;
//
//	uint8_t echoPortPin;
//
//	for (int i = 0; i < this->digitalPortsNumber; i++)
//	{
//		if (strcmp(this->digitalPort[i]->getUid(), this->triggerPortName))
//		{
//			triggerPortPin = this->digitalPort[i]->getPin();
//		}
//
//		if (this->digitalPort[i]->getUid() == this->echoPortName)
//		{
//			echoPortPin = this->digitalPort[i]->getPin();
//		}
//	}
//	if (triggerPortPin != NULL && echoPortPin != NULL)
//	{
//		return ultrasonicRepository.getDistance(triggerPortPin, echoPortPin);
//	}
//}






