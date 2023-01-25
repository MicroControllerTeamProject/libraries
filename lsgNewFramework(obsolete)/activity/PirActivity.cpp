#include "PirActivity.h"
#include "..\repository\AvrMicroRepository.h"

PirActivity::PirActivity(DigitalPort** digitalPirPorts, uint8_t digitalPirPortsNumber) : DeviceActivity(digitalPirPorts, digitalPirPortsNumber){
}

bool PirActivity::isThereAnyOne(AvrMicroRepository& avrMicroRepository){
	return this->isThereAnyDigitalPortOnAlarm(avrMicroRepository);
}
