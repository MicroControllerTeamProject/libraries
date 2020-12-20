#include <BTDynamicMenuTemplate.h>
#include <MyBlueTooth.h>
#include <BlueToothCommandsUtil.h>
#include <LSGEEpromRW.h>
#include <EEPROM.h> 
#include <StringFunctions.h> 

/// <summary>

/// </summary>
/// <param name="hardwareSerial"></param>
/// <param name="blueToothKeyPin"></param>
/// <param name="baseTransistorPin"></param>
/// <param name="baudRateProgramMode"></param>
/// <param name="baudRateReceveMode"></param>
/// <param name="softwareVersion"></param>
BTDynamicMenuTemplate::BTDynamicMenuTemplate(HardwareSerial* hardwareSerial, uint8_t blueToothKeyPin, uint8_t baseTransistorPin,
	long baudRateProgramMode, long baudRateReceveMode, char softwareVersion[15]) {

	eepromRW = new LSG_EEpromRW();

	myBlueTooth = new MyBlueTooth(hardwareSerial, blueToothKeyPin, baseTransistorPin, baudRateProgramMode, baudRateReceveMode);

	myBlueTooth->Reset_To_Slave_Mode();

	_version = softwareVersion;

	_oldPassword = myBlueTooth->GetPassword();

	//Serial.print("oldPassword : "); Serial.println(_oldPassword);

	myBlueTooth->ReceveMode();

	myBlueTooth->turnOnBlueTooth();
}

BTDynamicMenuTemplate::BTDynamicMenuTemplate(uint8_t blueToothKeyPin, uint8_t baseTransistorPin, long baudRateProgramMode,
	long baudRateReceveMode, uint8_t rx, uint8_t tx)
{
}

BTDynamicMenuTemplate::~BTDynamicMenuTemplate()
{
	delete eepromRW;
	delete myBlueTooth;
}

boolean BTDynamicMenuTemplate::isValidNumber(String str)
{
	for (byte i = 0; i < str.length(); i++)
	{
		if (isDigit(str.charAt(i))) return true;
	}
	return false;
}

void BTDynamicMenuTemplate::waitingForPhoneRequests(TransfertObject& transfertObject)
{
	_transfertObject = transfertObject;

	if (myBlueTooth->available())
	{
		_bluetoothData = myBlueTooth->readString();


		menuCaller();

		/*mainMenu();
		configurationMenu();*/
		mainMenuCommands();
		mainMenuData();

		configurationCommands();
		configurationData();

		securitySubMenu();
		securityMenuData();

		transfertObject = _transfertObject;
	}
}

void BTDynamicMenuTemplate::menuCaller()
{
	if (_bluetoothData.indexOf(F("#0")) > -1)
	{
		mainMenu();
	}

	if (_bluetoothData.indexOf(F("M001")) > -1)
	{
		configurationMenu();
	}

	if (_bluetoothData.indexOf(F("M004")) > -1)
	{
		securityMenu();
	}
}

void BTDynamicMenuTemplate::mainMenu()
{
	char* alarmStatus = new char[15];

	if (_transfertObject.isSystemActivated)
	{
		String(F("Sys:ON")).toCharArray(alarmStatus, 15);
	}
	else
	{
		String(F("Sys:OFF")).toCharArray(alarmStatus, 15);
	}

	char result[30];   // array to hold the result.

	strcpy(result, alarmStatus); // copy string one into the result.

	strcat(result, _version); // append string two to the result.

	//int internalTemperature = getTemp();//chipTemp->celsius();

	delete(alarmStatus);

	//String battery = calculateBatteryLevel(_voltageValue);

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(result, BlueToothCommandsUtil::Title));

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Configuration", BlueToothCommandsUtil::Menu, F("001")));

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Security", BlueToothCommandsUtil::Menu, F("004")));

	if (!_transfertObject.isSystemActivated)
	{
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Sys:On", BlueToothCommandsUtil::Command, F("002")));
	}
	else
	{
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Sys:Off", BlueToothCommandsUtil::Command, F("003")));
	}

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Temp.:" + String(_transfertObject._internalTemperature), BlueToothCommandsUtil::Info));

	///*myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Batt.value:" + String(_voltageValue), BlueToothCommandsUtil::Info));*/

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Batt.level:" + _transfertObject._batteryLevelGraf, BlueToothCommandsUtil::Info));

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("WhatzUp:" + String(_transfertObject._whatIsHappened), BlueToothCommandsUtil::Info));

	///*myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Signal:" + _signalStrength, BlueToothCommandsUtil::Info));*/

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));

	myBlueTooth->Flush();

}

void BTDynamicMenuTemplate::mainMenuCommands()
{
	if (_bluetoothData.indexOf(F("C002")) > -1)
	{
		/*_isAlarmOn = true;
		_isOnMotionDetect = false;
		_timeToTurnOnAlarm = 0;
		_isDisableCall = false;*/
		_transfertObject.isSystemActivated = true;
		mainMenu();
	}

	if (_bluetoothData.indexOf(F("C003")) > -1)
	{
		/*_isAlarmOn = false;*/
		_transfertObject.isSystemActivated = false;
		mainMenu();
	}
}

void BTDynamicMenuTemplate::mainMenuData() {}

void BTDynamicMenuTemplate::configurationMenu()
{
	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Configuration", BlueToothCommandsUtil::Title));

	//myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Phone:" + String(_phoneNumber), BlueToothCommandsUtil::Data, F("001")));

	//myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Ph.Altern.:" + String(_phoneNumberAlternative), BlueToothCommandsUtil::Data, F("099")));

	//myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("N.Phone:" + String(_phoneNumbers), BlueToothCommandsUtil::Data, F("098")));

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("TempMax:" + String(_transfertObject._internalTemperature), BlueToothCommandsUtil::Data, F("004")));

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("OffSetTemp:" + String(_transfertObject.offSetTemp), BlueToothCommandsUtil::Data, F("095")));

	////myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Apn:" + _apn, BlueToothCommandsUtil::Data, F("096")));

	//if (_findOutPhonesMode != 2)
	//{
	//	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("PIR status:" + String(_isPIRSensorActivated), BlueToothCommandsUtil::Data, F("005")));
	//}

	//if (_findOutPhonesMode != 0)
	//{
	//	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Addr:" + _deviceAddress, BlueToothCommandsUtil::Data, F("010")));

	//	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Name:" + _deviceName, BlueToothCommandsUtil::Data, F("011")));

	//	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Addr2:" + _deviceAddress2, BlueToothCommandsUtil::Data, F("015")));

	//	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Name2:" + _deviceName2, BlueToothCommandsUtil::Data, F("016")));

	//	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("FindLoop:" + String(_delayFindMe), BlueToothCommandsUtil::Data, F("094")));
	//}

	//myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("FindMode:" + String(_findOutPhonesMode), BlueToothCommandsUtil::Data, F("012")));

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Ext.Int:" + String(_transfertObject._isExternalInterruptOn), BlueToothCommandsUtil::Data, F("013")));

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor("Buzz.:" + String(_transfertObject.isBuzzerON), BlueToothCommandsUtil::Data, F("014")));

	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));

}

void BTDynamicMenuTemplate::configurationCommands() {}

void BTDynamicMenuTemplate::configurationData() {
	if (_bluetoothData.indexOf(F("D004")) > -1)
	{
		String splitString = StringFunctions::SplitStringIndex(_bluetoothData, ';', 1);
		if (isValidNumber(splitString))
		{
			char data[5];
			splitString.toCharArray(data, 6);
			_transfertObject._internalTemperature = atof(&data[0]);
			_transfertObject.isDataChanged = true;
		}
		configurationMenu();
	}

	if (_bluetoothData.indexOf(F("D013")) > -1)
	{
		String splitString = StringFunctions::SplitStringIndex(_bluetoothData, ';', 1);
		if (isValidNumber(splitString))
		{
			char data[2];
			splitString.toCharArray(data, 2);
			_transfertObject._isExternalInterruptOn = atoi(&data[0]);;
			_transfertObject.isDataChanged = true;
		}
		configurationMenu();
	}

	if (_bluetoothData.indexOf(F("D014")) > -1)
	{
		String splitString = StringFunctions::SplitStringIndex(_bluetoothData, ';', 1);
		if (isValidNumber(splitString))
		{
			char data[2];
			splitString.toCharArray(data, 2);
			_transfertObject.isBuzzerON = atoi(&data[0]);;
			_transfertObject.isDataChanged = true;
		}
		configurationMenu();
	}

	if (_bluetoothData.indexOf(F("D095")) > -1)
	{
		String splitString = StringFunctions::SplitStringIndex(_bluetoothData, ';', 1);
		if (isValidNumber(splitString))
		{
			char data[4];
			splitString.toCharArray(data, 4);
			_transfertObject.offSetTemp = atoi(&data[0]);
			_transfertObject.isDataChanged = true;
		}
		configurationMenu();
	}
}

void BTDynamicMenuTemplate::securityMenu() {
	//_timeToTurnOnAlarm = millis() + 300000;
	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Security"), BlueToothCommandsUtil::Title));
	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Change passw.:"), BlueToothCommandsUtil::Menu, F("005")));
	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Change name:"), BlueToothCommandsUtil::Menu, F("006")));
	myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));
	myBlueTooth->Flush();
}

void BTDynamicMenuTemplate::securitySubMenu()
{
	if (_bluetoothData.indexOf(F("M005")) > -1)
	{
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Change passw."), BlueToothCommandsUtil::Title));
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Insert old passw.:"), BlueToothCommandsUtil::Data, F("006")));
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));
	}
	if (_bluetoothData.indexOf(F("M006")) > -1)
	{
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Change name."), BlueToothCommandsUtil::Title));
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Insert name:"), BlueToothCommandsUtil::Data, F("007")));
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));
	}
}

void BTDynamicMenuTemplate::securityMenuCommands() {}

void BTDynamicMenuTemplate::securityMenuData()
{
	if (_bluetoothData.indexOf(F("D006")) > -1)
	{
		String confirmedOldPassword = StringFunctions::SplitStringIndex(_bluetoothData, ';', 1);

		if (_oldPassword == confirmedOldPassword)
		{
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Change passw."), BlueToothCommandsUtil::Title));
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Insert new passw:"), BlueToothCommandsUtil::Data, F("008")));
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));
		}
		else
		{
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Change passw."), BlueToothCommandsUtil::Title));
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Wrong passw:"), BlueToothCommandsUtil::Message));
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));
		}

	}

	if (_bluetoothData.indexOf(F("D008")) > -1)
	{
		_newPassword = StringFunctions::SplitStringIndex(_bluetoothData, ';', 1);
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Change passw."), BlueToothCommandsUtil::Title));
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Confirm pass:"), BlueToothCommandsUtil::Data, F("009")));
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));
	}

	if (_bluetoothData.indexOf(F("D009")) > -1)
	{
		if (_newPassword == StringFunctions::SplitStringIndex(_bluetoothData, ';', 1))
		{
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Change passw."), BlueToothCommandsUtil::Title));
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("changed:"), BlueToothCommandsUtil::Message));
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));
			delay(2000);
			myBlueTooth->SetPassword(_newPassword);
			_oldPassword = _newPassword;
		}

		else
		{
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Change passw."), BlueToothCommandsUtil::Title));
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("passw. doesn't match"), BlueToothCommandsUtil::Message));
			myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));
			myBlueTooth->println("D006");
		}
	}

	if (_bluetoothData.indexOf(F("D007")) > -1)
	{
		String btName = StringFunctions::SplitStringIndex(_bluetoothData, ';', 1);

		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("Change passw."), BlueToothCommandsUtil::Title));
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(F("changed:"), BlueToothCommandsUtil::Message));
		myBlueTooth->println(BlueToothCommandsUtil::CommandConstructor(BlueToothCommandsUtil::EndTrasmission));
		delay(2000);
		myBlueTooth->SetBlueToothName(btName);
	}
}


