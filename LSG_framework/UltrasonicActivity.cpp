#include "UltrasonicActivity.h"
#include <Ultrasonic.h>


//Send two DigitalPort objects,one with the uid equal to parameter triggerPortName,and second with uid equal to echoPortName. 
UltrasonicActivity::UltrasonicActivity(DigitalPort** digitalPort, 
	uint8_t digitalPortsNumber,
	String triggerPortName, 
	String echoPortName) : DeviceActivity(digitalPort, digitalPortsNumber)
{
	this->digitalPort = digitalPort;
	this->digitalPortsNumber = digitalPortsNumber;
	this->triggerPortName = triggerPortName;
	this->echoPortName = echoPortName;
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

float UltrasonicActivity::getDistance() {
	return getUnitOfMisureValue();
}

float UltrasonicActivity::getUnitOfMisureValue()
{
	Ultrasonic* ultrasonic;

	uint8_t triggerPortPin;

	uint8_t echoPortPin;

	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		if (this->digitalPort[i]->getUid() == this->triggerPortName)
		{
			triggerPortPin = this->digitalPort[i]->getPin();
		}

		if (this->digitalPort[i]->getUid() == this->echoPortName)
		{
			echoPortPin = this->digitalPort[i]->getPin();
		}
	}
	if (triggerPortPin != NULL && echoPortPin != NULL)
	{
		ultrasonic = new Ultrasonic(triggerPortPin, echoPortPin);
		return ultrasonic->distanceRead();
	}
}






