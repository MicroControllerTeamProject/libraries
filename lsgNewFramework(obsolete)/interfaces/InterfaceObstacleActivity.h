#pragma once
#include <stdint.h>
	class InterfaceObstacleActivity
	{
	public:
		virtual ~InterfaceObstacleActivity() {}
		virtual bool isObstacleDetected(char* uid) = 0;
		virtual bool isSensorOnError() = 0;
		virtual uint16_t getDistance() = 0;
	};


