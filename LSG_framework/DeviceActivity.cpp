#include "DeviceActivity.h"

DeviceActivity::DeviceActivity(){
}

DeviceActivity::DeviceActivity(DigitalPort** digitalPort,  uint8_t digitalPortsNumber)
{
	this->digitalPort = digitalPort;
	this->digitalPortsNumber = digitalPortsNumber;

	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		if (this->digitalPort[i]->direction == output)
		{
			pinMode(this->digitalPort[i]->pin, OUTPUT);
		}
		else
		{
			if (this->digitalPort[i]->isOnPullUp) {
				pinMode(this->digitalPort[i]->pin, INPUT_PULLUP);
			}
			else
			{
				pinMode(this->digitalPort[i]->pin, INPUT);
			}
		}
	}
}

DeviceActivity::DeviceActivity(AnalogPort** analogPort,float vref, uint8_t analogPortsNumber)
{
	this->analogPort = analogPort;
	this->analogPortsNumber = analogPortsNumber;
	this->vref = vref;

	//for (int i = 0; i < this->analogPortsNumer; i++)
	//{
	//	if (this->analogPort[i]->direction == output)
	//	{
	//		pinMode(this->analogPort[i]->pin, OUTPUT);
	//	}
	////	else
	////	{
	////		if (this->analogPort[i]->isOnPullUp) {
	////			pinMode(this->digitalPort[i]->pin, INPUT_PULLUP);
	////			Serial.println("pin= INPUT_PULLUP");
	////		}
	////		else
	////		{
	////			pinMode(this->digitalPort[i]->pin, INPUT);
	////		}
	////	}
	////}
}


bool DeviceActivity::isThereAnyCustomMisureOnAlarm(float minCustomValue,float maxCustomValue,String measureDescription)
{
	if (getUnitOfMisureValue() > maxCustomValue)
	{
		this->lastAlarmDescription = measureDescription + " level HIGH";
	}
	if (getUnitOfMisureValue() < minCustomValue)
	{
		this->lastAlarmDescription = measureDescription + " level LOW";
	}
}

/// <summary>
/// check all ports to find an alarm
/// </summary>
/// <returns></returns>
bool DeviceActivity::isThereAnyPortOnAlarm()
{
	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		if (this->digitalPort[i]->alarmOn == DigitalPort::AlarmOn::low && digitalRead(this->digitalPort[i]->pin) == LOW)
		{
			this->lastAlarmDescription = digitalPort[i]->uid + " level LOW";
			return true;
			
		}
		if (this->digitalPort[i]->alarmOn == DigitalPort::AlarmOn::high && digitalRead(this->digitalPort[i]->pin) == HIGH)
		{
			return true;
		}
	}

	for (int i = 0; i < this->analogPortsNumber; i++)
	{
		if (this->analogPort[i]->maxVoltageAlarmValueIn > (this->vref /1023) * analogRead(this->analogPort[i]->pin))
		{
			this->lastAlarmDescription = analogPort[i]->uid + " level too HIGH";
			return true;
		}

		if (this->analogPort[i]->minVoltageAlarmValueIn < (this->vref / 1023) * analogRead(this->analogPort[i]->pin))
		{
			this->lastAlarmDescription = analogPort[i]->uid + " level too LOW";
			return true;
		}
	}
	return false;
}

String DeviceActivity::getLastAlarmDescription()
{
	return this->lastAlarmDescription;
}

String DeviceActivity::getLastErrorDescription()
{
	return this->lastErrorDescription;
}

float DeviceActivity::analogReadVoltageByName(String analogPortName)
{
	for (int i = 0; i < this->analogPortsNumber; i++)
	{
		if (this->analogPort[i]->uid == analogPortName)
		{
			return (this->vref /1023) * analogRead(this->analogPort[i]->pin);
			/*else
			{
				lastError = this->analogPort[i]->uid + String(" is not output mode");
				return false;
			}*/
		}
	}
}

int DeviceActivity::analogReadByName(String analogPortName)
{
	for (int i = 0; i < this->analogPortsNumber; i++)
	{
		if (this->analogPort[i]->uid == analogPortName)
		{
			return (this->vref / 1023) * analogRead(this->analogPort[i]->pin);
			/*else
			{
				lastError = this->analogPort[i]->uid + String(" is not output mode");
				return false;
			}*/
		}

	}
}

bool DeviceActivity::digitalWriteByName(String digitalPortName,uint8_t pinLevel)
{
	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		if (this->digitalPort[i]->uid == digitalPortName)
		{
			if (this->digitalPort[i]->direction == output)
			{
				digitalWrite(this->digitalPort[i]->pin, pinLevel);
				return true;
			}
			else
			{
				lastErrorDescription = this->digitalPort[i]->uid + String(" is not output mode");
				return false;
			}
		}
		
	}
}

uint8_t DeviceActivity::digitalReadByName(String digitalPortName)
{
	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		if (this->digitalPort[i]->uid == digitalPortName && this->digitalPort[i]->direction == input)
		{
			return digitalRead(this->digitalPort[i]->pin);
		}
	}
}

float DeviceActivity::getUnitOfMisureValue(String analogPortName)
{
	float mathRelationship;
	for (int i = 0; i < this->analogPortsNumber; i++)
	{
		if (this->analogPort[i]->uid == analogPortName)
		{
			mathRelationship = this->analogPort[i]->unitOfMisureFullScale / this->vref;
			return ((this->vref / 1023) * analogRead(this->analogPort[i]->pin)) * mathRelationship;
			/*else
			{
				lastError = this->analogPort[i]->uid + String(" is not output mode");
				return false;
			}*/
		}

	}
}

float  DeviceActivity::getUnitOfMisureValue() {
}




