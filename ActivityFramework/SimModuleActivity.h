#pragma once
#include "DeviceActivity.h"
#include "SimModuleDevice.h"
#include "InterfaceSerialRepository.h"
#include "SimProgMemRepository.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


class SimModuleActivity : public DeviceActivity
{
public:
	/*SimModuleActivity(InterfaceSerialRepository& simModuleRepository, AvrMicroRepository& avrMicroRepository, SimModuleDevice** listOfSimModuleDevice, uint8_t simModuleDevicesNumber);*/
	SimModuleActivity(InterfaceSerialRepository& simModuleRepository, SimProgMemRepository& simProgMemRepository,  AvrMicroRepository& avrMicroRepository, SimModuleDevice& simModuleDevice);
	SimModuleActivity();
	void makeCall(char buffer[], uint8_t bufferLenght);
	/*void enableIncomingSMS();*/
	void setIsDisableSms(bool isSmsDisabled);
	bool getIsDisableSms();
	void setIsCallDisabled(bool isCallDisabled);
	bool getIsCallDisabled();
	void setIsInSleepMode(bool isInSleepMode);
	bool getIsInSleepMode(bool isInSleepMode);
	bool setIsDeviceTurnedOff(bool isTurnedOff, char* deviceUid);
	bool getIsDeviceTurnedOff();
	uint8_t _simModuleDevicesNumber = 0;
	SimModuleDevice* _simModuleDevice = nullptr;
	InterfaceSerialRepository* _simModuleRepository = nullptr;
	SimProgMemRepository* _simProgMemRepository = nullptr;
	/*AvrMicroRepository* _avrMicroRepository = nullptr;*/
	uint8_t getNumberOfSmsReceived();
	void sendProgMemAtCommand(uint16_t progMemIndex);
	void enableSmsIncoming();

	void deleteAllSMS();

	
	void getSmsByIndex(uint8_t index);

	bool getSmsResponse(char* bufferP, uint16_t bufferLenght);

	bool isSmsOnBuffer(char* response, uint16_t progMemIndex, uint8_t maxMessageLenght);

	void deleteSmsByIndex(uint8_t index);



	void extractSmsMessageFromReponse(char* response, char* messageBuffer, uint16_t messageLength);

	bool isCallerAuthorized(char* response, char* phoneNumberToCheck);

private:
	char* subStringBetweenTags(char* p_string, char tag[1], uint16_t position, char* buffer);

	bool _isSmsDisabled = false;
	bool _isCallDisable = false;
	bool _isTurnedOff = false;
	bool _isInSleepMode = false;
	long unsigned _baud = 0;
};

