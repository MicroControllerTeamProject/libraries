#include "SoftwareSerialRepository.h"


SoftwareSerialRepository::SoftwareSerialRepository() {
}

SoftwareSerialRepository::~SoftwareSerialRepository()
{
	if (this->softwareSerial != nullptr)
	{
		delete this->softwareSerial;
	}
}

void SoftwareSerialRepository::init(uint8_t rx, uint8_t tx, bool inv_logic){
	this->_rxPin = rx;
	this->_txPin = tx;
	this->invers_logic = inv_logic;
	this->softwareSerial = new SoftwareSerial(rx, tx, inv_logic);
}

//void SoftwareSerialRepository::print_m(const char* data,bool isNewLine = false)
//{
//	if (this->softwareSerial != nullptr)
//	{
//		this->softwareSerial->print(data);
//	}
//}

void SoftwareSerialRepository::print_m(float data)
{
	if (this->softwareSerial != nullptr)
	{
		this->softwareSerial->print(data);
	}
}

void SoftwareSerialRepository::println(const char* data)
{
	if (this->softwareSerial != nullptr)
	{
		this->softwareSerial->println(data);
	}
	
}

void SoftwareSerialRepository::println(float data)
{
	if (this->softwareSerial != nullptr)
	{
		this->softwareSerial->println(data);
	}

}

bool SoftwareSerialRepository::serial_available()
{
	if (this->softwareSerial != nullptr)
	{
		if (softwareSerial->available() > 0)
		{
			return true;
		}
	}
}

int SoftwareSerialRepository::read() {
	if (softwareSerial != nullptr)
	{
		return softwareSerial->read();
	}
}

char* SoftwareSerialRepository::readString() {
	char a[250];
	char b[500];
	String c;
	if (softwareSerial != nullptr)
	{
		while (softwareSerial->available() > 0) {
			c.concat((char)softwareSerial->read());
		}
		c.toCharArray(a, c.length());
		strcpy(b, a);
		return b;
	}
	
}

char* SoftwareSerialRepository::readBuffer()
{
	char a[250];
	char b[500];
	String c;
	if (softwareSerial != nullptr)
	{
		c = softwareSerial->readString();
		c.toCharArray(a, c.length());
		strcpy(b, a);
		return b;
	}
	
}
