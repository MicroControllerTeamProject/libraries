#pragma once
#include <stdint.h>

class I2COstacleSensor
{
public:
	I2COstacleSensor(uint8_t address, char* uid, uint16_t minDistanceToObstacle);
	char* getUid();
	uint16_t getAddress();
	void enable(bool isEnable);
	bool isEnable();
	uint8_t _address;
	char* _uid;
	uint8_t _minDistanceToObstacle = 0;
	bool _isEnable = true;
};

