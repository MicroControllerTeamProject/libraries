#include <BlueToothCommandsUtil.h>


BlueToothCommandsUtil::BlueToothCommandsUtil()
{
}


BlueToothCommandsUtil::~BlueToothCommandsUtil()
{
}

//used for command 
String BlueToothCommandsUtil::CommandConstructor(String commandString, BlueToothCommandsUtil::CommandTypeA commandType, String commandCode)
{
	commandString = commandString + F(";");
	switch (commandType)
	{

	case  BlueToothCommandsUtil::Command:
		return commandString + F("C") + commandCode;
		break;
	case  BlueToothCommandsUtil::Data:
		return commandString + F("D") + commandCode;
		break;
	case  BlueToothCommandsUtil::Menu:
		return commandString + F("M") + commandCode;
		break;
	default:
		break;
	}
}

//Used for message and title 
String BlueToothCommandsUtil::CommandConstructor(String commandString, BlueToothCommandsUtil::CommandTypeC commandType)
{
	commandString = commandString + F(";");
	switch (commandType)
	{
	case  BlueToothCommandsUtil::Message:
		return commandString + F("MES");
		break;
	case  BlueToothCommandsUtil::Title:
		return commandString + F("TIT");
		break;
	case  BlueToothCommandsUtil::Info:
		return commandString + F("INF");
		break;
	default:
		break;
	}
}

//Used for endtrasmission
String BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::CommandTypeB commandType)
{
	switch (commandType)
	{
	case  BlueToothCommandsUtil::EndTrasmission:
		return F(";E");
		break;
	default:
		break;
	}
}