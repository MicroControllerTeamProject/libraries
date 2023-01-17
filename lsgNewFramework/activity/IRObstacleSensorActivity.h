#pragma once
#include "DeviceActivity.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\model\DigitalPort.h"
#include "..\commons\commonsLayer.h"
#include "..\interfaces\InterfaceObstacleActivity.h"
#include "..\interfaces\IDigitalPorts.h"
#include "..\objectsSensor\DigitalPortSensor.h"

class IRObstacleSensorActivity : public DeviceActivity,public InterfaceObstacleActivity
{
public:
	IRObstacleSensorActivity(AvrMicroRepository& avrMicroRepository, DigitalPortSensor** obstacleDigitalSensor,uint8_t obstacleDigitalSensorsNumber);
	virtual bool isObstacleDetected(char* uid);
	virtual bool isSensorOnError();
	virtual uint16_t getDistance();
private:
};

