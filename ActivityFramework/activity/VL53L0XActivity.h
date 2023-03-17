#pragma once
#include "..\interfaces\InterfaceObstacleActivity.h"
#include "..\repository\VL53L0XRepository.h"
#include "..\objectsSensor\I2COstacleSensor.h"
#include <string.h>
#include <stdlib.h>

class VL53L0XActivity :  public InterfaceObstacleActivity
{
public:
	VL53L0XActivity(VL53L0XRepository& vl53L0XRepository, I2COstacleSensor** listOfi2COstacleSensor, uint8_t i2COstacleSensorsNumber);
	virtual bool isObstacleDetected(char* uid);
	virtual bool isSensorOnError();
	virtual uint16_t getDistance();
	VL53L0XRepository* _vl53L0XRepository = nullptr;
	I2COstacleSensor** _listOfi2COstacleSensor = nullptr;
	uint8_t _i2COstacleSensorsNumber = 0;
};

