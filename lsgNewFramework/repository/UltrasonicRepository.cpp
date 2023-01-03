#include "UltrasonicRepository.h"
#include <Ultrasonic.h>


UltrasonicRepository::UltrasonicRepository(){
}

unsigned int UltrasonicRepository::getDistance(uint8_t triggerPortPin, uint8_t echoPortPin,unsigned long timeout)
{
	return Ultrasonic(triggerPortPin, echoPortPin,timeout).distanceRead();
}
