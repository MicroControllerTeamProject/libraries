#pragma once
#include "..\interfaces\InterfaceObstacleActivity.h"
#include "..\repository\VL53L0XRepository.h"

class VL53L0XActivity :  public InterfaceObstacleActivity
{
public:
	VL53L0XActivity(VL53L0XRepository& vl53L0XRepository);
	virtual bool isObstacleDetected(char* uid);
	virtual bool isSensorOnError();
};

