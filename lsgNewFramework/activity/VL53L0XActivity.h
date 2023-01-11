#pragma once
#include "..\interfaces\IntrefaceObstacleSensor.h"
#include "..\repository\VL53L0XRepository.h"

class VL53L0XActivity :  public InterfaceObstacleSensor
{
public:
	VL53L0XActivity(VL53L0XRepository& vl53L0XRepository);
};

