#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>
class MySim900
{
	//public: int GetData3();
//public: void WaitSMSComing();
//public:	void SIM900power();
public:
	MySim900(uint8_t rx, uint8_t tx,bool invers_logic);
	~MySim900();
	//void WaitSMSComing();
	void Begin(long speed);
	//void SIM900power();
	void DialVoiceCall(char* phoneNumber);
	void SendTextMessage(char* phoneNumber, char* message);
	//bool IsWorking();
	//char* ReadIncomingChars();
	String ReadIncomingChars2();
	//String ReadIncomingChars3();
	void SendTextMessageAndMeasure(char* phoneNumber, char* message, float measure);
	void Flush();
	void ClearBuffer(unsigned long timeOut);
	void ATCommand(char* atCommand);
	bool IsAvailable();
	//void Delete();
	void IsSmsDisabled(bool isDisabled);
	void IsCallDisabled(bool isDisabled);
	void SendTextMessageSimple(String message, String phoneNumber);
	String GetSignalStrength();
	void enableIncomingCall(uint8_t numberOfRings);
	void disableIncomingCall();
private:
	bool _isSmsDisabled;
	bool _isCallDisabled;
	SoftwareSerial* SIM900;
};

