#pragma once
	class InterfaceObstacleActivity
	{
	public:
		virtual ~InterfaceObstacleActivity() {}
		virtual bool isObstacleDetected(char* uid) = 0;
		virtual bool isSensorOnError() = 0;
	};


