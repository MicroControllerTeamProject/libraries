#pragma once
#include <Arduino.h>
class BlueToothCommandsUtil
{
public:
	BlueToothCommandsUtil();
	~BlueToothCommandsUtil();
	enum CommandTypeA { Command, Data, Menu };
	enum CommandTypeB { EndTrasmission };
	enum CommandTypeC { Message, Title ,Info};

	static String CommandConstructor(String commandString, BlueToothCommandsUtil::CommandTypeA commandType, String commandCode);
	static String CommandConstructor(BlueToothCommandsUtil::CommandTypeB commandType);
	static String CommandConstructor(String commandString, BlueToothCommandsUtil::CommandTypeC commandType);
};