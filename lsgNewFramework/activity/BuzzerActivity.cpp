#include "BuzzerActivity.h"
BuzzerActivity::BuzzerActivity(AvrMicroRepository avrMicroRepository, DigitalPort** digitalPort, uint8_t digitalPortsNumber) :DeviceActivity(avrMicroRepository, digitalPort, digitalPortsNumber) {
}
void BuzzerActivity::alarm1()
{
	for (int i = 500; i < 1500; i++)
	{
		this->_avrMicroRepository.tone_m(8, i, 100);
	}
}
void BuzzerActivity::alarm2()
{
	for (int i = 500; i < 1500; i++)
	{
		this->_avrMicroRepository.tone_m(8, i, 10);
		this->_avrMicroRepository.delaym(5);
	}
	for (int i = 1500; i > 500; i--)
	{
		this->_avrMicroRepository.tone_m(8, i, 10);
		this->_avrMicroRepository.delaym(5);
	}
}
void BuzzerActivity::alarm3()
{
	this->_avrMicroRepository.tone_m(8, 400, 500);
	this->_avrMicroRepository.delaym(500);
	this->_avrMicroRepository.tone_m(8, 800, 500);
	this->_avrMicroRepository.delaym(500);

}

