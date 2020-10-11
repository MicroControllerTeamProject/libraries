#include "MySim900.h"
#include "StringFunctions.h"

MySim900::MySim900(uint8_t rx, uint8_t tx, bool invers_logic)
{
	SIM900 = new SoftwareSerial(rx, tx, invers_logic);
	IsCallDisabled(false);
	IsSmsDisabled(false);
}

void MySim900::Begin(long speed)
{
	SIM900->begin(speed); // for GSM shield
}

MySim900::~MySim900()
{
	if (SIM900 != NULL)
	{
		delete SIM900;
	}

}

bool MySim900::IsAvailable()
{
	if (SIM900->available() > 0)
		return true;
	else
		return false;
}

void MySim900::ClearBuffer(unsigned long timeOut) {
	SIM900->setTimeout(timeOut);
	SIM900->readString();

}
//
//String MySim900::ReadIncomingChars2()
//{
//	//String response = "";
//	if (SIM900->available() > 0)
//	{
//		return SIM900->readString();
//	}
//}

String MySim900::ReadIncomingChars2()
{
	String response = "";
	if (SIM900->available() >0)
	{

		while (SIM900->available() > 0) {
			response.concat((char)SIM900->read());
		}
		return response;
	}
}

///Sembra non funzionare Obsolete
//char* MySim900::ReadIncomingChars()
//{
//
//	//char result[64] ="";   // array to hold the result.
//	String response = "";
//	// Now we simply display any text that the GSM shield sends out on the serial monitor
//	//	CODICE DI ATTESA PER LEGGERE SMS IN INGRESSO
//
//	if (SIM900->available() > 0)
//	{
//
//		while (SIM900->available()) {
//			response.concat((char)SIM900->read());
//		}
//		//Serial.println(response); 
//		char* buffer;
//		response.toCharArray(buffer, response.length());
//		//Serial.println(a);
//		return buffer;
//	}
//}

//DA RICHIAMARE DAL SETUP PER ATTIVARE ATTESA SMS
//void MySim900::WaitSMSComing()
//{
//	SIM900->print(F("AT + IPREX = 19200\r"));
//	delay(100);
//	SIM900->print(F("AT+CMGF=1\r"));  // set SMS mode to text
//	delay(100);
//	SIM900->print(F("AT+CNMI=2,2,0,0,0\r"));
//	// blurt out contents of new SMS upon receipt to the GSM shield's serial out
//	delay(100);
//}

//void MySim900::SIM900power()
//// software equivalent of pressing the GSM shield "power" button
//{
//	//pinMode(9, OUTPUT);
//	//delay(5000);  // give time to log on to network.
//	digitalWrite(9, HIGH);
//	delay(500);
//	digitalWrite(9, LOW);
//	delay(7000);
//	digitalWrite(9, HIGH);
//
//	/*digitalWrite(9, LOW);
//	delay(3000);*/
//}

void MySim900::DialVoiceCall(char* phoneNumber)
{

	if (_isCallDisabled) return;

	char result[25];   // array to hold the result.
	strcpy(result, "ATD + "); // copy string one into the result.
	strcat(result, phoneNumber); // append string two to the result.
	strcat(result, ";");

	//SIM900.println("ATD + +393397510192;");//dial the number 
	SIM900->println(result);//dial the number 
	/*delay(100);
	SIM900->println();*/
}

void MySim900::SendTextMessageAndMeasure(char* phoneNumber, char* message, float measure)
{
	if (_isSmsDisabled) return;

	char result[28] = "";   // array to hold the result.
	strcpy(result, "AT + CMGS = \""); // copy string one into the result.
	strcat(result, phoneNumber); // append string two to the result.
	strcat(result, "\"");
	SIM900->print(F("AT+CMGF=1\r"));    //Because we want to send the SMS in text mode
	delay(100);
	//SIM900.println("AT + CMGS = \"+393397510192\"");//send sms message, be careful need to add a country code before the cellphone number
	SIM900->println(result);//send sms message, be careful need to add a country code before the cellphone number
	delay(100);

	if (measure < -9000)
	{
		SIM900->println(message);
	}
	else
	{
		SIM900->print(message); SIM900->print(F(" ")); SIM900->println(measure);//the content of the message
	}

	delay(100);
	SIM900->println((char)26);//the ASCII code of the ctrl+z is 26
	delay(100);
	SIM900->println();

}

String MySim900::GetSignalStrength()
{
	SIM900->println(F("AT+CSQ"));
	delay(1000);
	String getData = "";
	String valueString = "";

	if (IsAvailable())
	{
		getData = SIM900->readString();
		if (getData.indexOf("+CSQ:") > -1)
		{
			String fullString = StringFunctions::SplitStringIndex(getData.substring(getData.indexOf("+CSQ:")), '\r', 0);
			valueString = StringFunctions::SplitStringIndex(fullString, ':', 1);
		}
	}
	return valueString;
}

void MySim900::SendTextMessage(char* phoneNumber, char* message)
{
	SendTextMessageAndMeasure(phoneNumber, message, -10000.00);
}

void MySim900::SendTextMessageSimple(String message, String phoneNumber)
{
	//*Serial.println(message);
	//return;*/
	//message = "google.com/maps/search/?api=1&query=45.511208,9.244042";
	////ClearBuffer(1000);
	////SIM900->println(F("AT"));    //Because we want to send the SMS in text mode
	////delay(1000);
	SIM900->println(F("AT+CMGF=1;"));    //Because we want to send the SMS in text mode
	delay(100);
	String atCommand = "AT+CMGS=\"" + phoneNumber + "\"";
	SIM900->println(atCommand);//send sms message, be careful need to add a country code before the cellphone number
	//SIM900->println("AT+CMGS=\"+393397510192\"");
	delay(100);
	SIM900->println(message);//the content of the message
	delay(100);
	SIM900->println((char)26);//the ASCII code of the ctrl+z is 26
	delay(1000);
	//SIM900->println();
}

void MySim900::Flush()
{
	SIM900->end();
	SIM900->flush();
	SIM900->clearWriteError();
}

void MySim900::ATCommand(char* atCommand)
{
	SIM900->println(atCommand);
}

void MySim900::IsSmsDisabled(bool isDisabled)
{
	_isSmsDisabled = isDisabled;
}

void MySim900::IsCallDisabled(bool isDisabled)
{
	_isCallDisabled = isDisabled;
}

//void MySim900::TurnOnDeviceNoCkeckNetwork(uint8_t powerPin, boolean force)
//{
//		pinMode(powerPin, OUTPUT);
//		SIM900->println("AT");
//		delay(1000);
//		if (!IsAvailable() || force)
//		{
//			digitalWrite(powerPin, HIGH);
//			delay(500);
//			digitalWrite(powerPin, LOW);
//		}
//}
//
//void MySim900::TurnOffDeviceNoCkeckNetwork(uint8_t powerPin, boolean force)
//{
//		pinMode(powerPin, OUTPUT);
//		digitalWrite(powerPin, HIGH);
//		delay(500);
//		digitalWrite(powerPin, LOW);
//		delay(500);
//		digitalWrite(powerPin, HIGH);
//		//digitalWrite(powerPin, HIGH);
//}
///Obsolete
//void MySim900::TurnOnDeviceYesCkeckNetwork()
//{
//	char* response;
//	SIM900->println("AT + CGMR");
//	delay(5000);
//	if (!IsAvailable() || false)
//	{
//		pinMode(9, OUTPUT);
//		//Serial.println("Sim Power On");
//		digitalWrite(9, HIGH);
//		delay(100);
//		digitalWrite(9, LOW);
//		delay(5000);
//		digitalWrite(9, HIGH);
//
//
//		//Serve per attivare velocemente la Sim
//
//		////lunga attesa necessaria.
//		//delay(5000);
//		bool cicle = true;
//		bool step1 = false;
//		bool step2 = false;
//		bool step3 = false;
//		while (cicle)
//		{
//			response = ReadIncomingChars();
//			String buffer = response;
//			//Serial.println(buffer);
//			if (buffer.substring(0, 10) == F("Call Ready"))
//			{
//				//printSerialAndLCDFunctions.WriteSimpleMessage(0, 0, "Call Ready", true, 0);
//				//Serial.println("Call Ready");
//				step3 = true;
//			}
//
//			if (buffer.substring(0, 12) == F("+CPIN: READY"))
//			{
//				//Serial.println("+CPIN: READY");
//				//printSerialAndLCDFunctions.WriteSimpleMessage(0, 1, "+CPIN: READY", true, 0);
//				step2 = true;
//			}
//			if (step3)
//			{
//				//printSerialAndLCDFunctions.WriteSimpleMessage(0, 3, "SIM Steps Passed", true, 3);
//				cicle = false;
//			}
//		}
//
//	}
//}

