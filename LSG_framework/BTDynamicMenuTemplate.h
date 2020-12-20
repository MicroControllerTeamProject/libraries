#pragma once
#include <Arduino.h>
#include <pins_arduino.h>
#include <TransfertObject.h>
#include <LSGEEpromRW.h>
#include <MyBlueTooth.h>

class BTDynamicMenuTemplate
{
public:
	BTDynamicMenuTemplate(HardwareSerial* hardwareSerial,
		uint8_t blueToothKeyPin,
		uint8_t baseTransistorPin,
		long baudRateProgramMode,
		long baudRateReceveMode, char version[15]);
	BTDynamicMenuTemplate(uint8_t blueToothKeyPin,
		uint8_t baseTransistorPin,
		long baudRateProgramMode,
		long baudRateReceveMode,
		uint8_t rx, uint8_t tx);
	void waitingForPhoneRequests(TransfertObject &transfertObject);
	~BTDynamicMenuTemplate();
private:
	String _bluetoothData = "";
	String _oldPassword;
	String _newPassword;
	char* _version;
	TransfertObject _transfertObject;
	LSG_EEpromRW* eepromRW;
	MyBlueTooth* myBlueTooth;
	boolean isValidNumber(String str);
protected:
	virtual void mainMenu();
	virtual void mainMenuCommands();
	virtual void mainMenuData();
	virtual void configurationMenu();
	virtual void configurationData();
	virtual void configurationCommands();
	virtual void securityMenu();
	virtual void securitySubMenu();
	virtual void securityMenuCommands();
	virtual void securityMenuData();
	virtual void menuCaller();
};

