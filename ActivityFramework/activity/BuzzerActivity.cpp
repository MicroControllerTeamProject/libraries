#include "BuzzerActivity.h"
BuzzerActivity::BuzzerActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** digitalPort) : DeviceActivity(avrMicroRepository, digitalPort) {
}
void BuzzerActivity::alarm1(uint8_t numberOfCicle)
{
	if (!this->getAllDigitalPorts()[0]->isEnable) return;
	for (int ii = 0; ii < numberOfCicle; ii++)
	{
		for (int i = 500; i < 1500; i++)
		{
			this->avrMicroRepository->tone_m(this->getAllDigitalPorts()[0]->getPin(), i, 100);
		}
	}
}

void BuzzerActivity::alarm2(uint8_t numberOfCicle)
{
	if (!this->getAllDigitalPorts()[0]->isEnable) return;
	for (int ii = 0; ii < numberOfCicle; ii++)
	{
		for (int i = 500; i < 1500; i++)
		{
			this->avrMicroRepository->tone_m(this->getAllDigitalPorts()[0]->getPin(), i, 10);
			this->avrMicroRepository->delaym(5);
		}
		for (int i = 1500; i > 500; i--)
		{
			this->avrMicroRepository->tone_m(this->getAllDigitalPorts()[0]->getPin(), i, 10);
			this->avrMicroRepository->delaym(5);
		}
	}
}

void BuzzerActivity::alarm3(uint8_t numberOfCicle)
{
	if (!this->getAllDigitalPorts()[0]->isEnable) return;
	for (int ii = 0; ii < numberOfCicle; ii++)
	{
		this->avrMicroRepository->tone_m(this->getAllDigitalPorts()[0]->getPin(), 400, 500);
		this->avrMicroRepository->delaym(500);
		this->avrMicroRepository->tone_m(this->getAllDigitalPorts()[0]->getPin(), 800, 500);
		this->avrMicroRepository->delaym(500);
	}

}

