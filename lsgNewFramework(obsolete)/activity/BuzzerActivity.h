#pragma once
#include "DeviceActivity.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\model\DigitalPort.h"
#include "..\commons\commonsLayer.h"
class BuzzerActivity : public DeviceActivity
{
public:
	BuzzerActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** digitalPort);
	void alarm1(uint8_t numberOfCicle);
	void alarm2(uint8_t numberOfCicle);
	void alarm3(uint8_t numberOfCicle);
	//void alarm4();
	//void alarm5();
	//void alarm6();
	//void signal1();
	//void signal2();
	//void signal3();
	//void signal4();
	//void signal5();
	//void signal6();
};

