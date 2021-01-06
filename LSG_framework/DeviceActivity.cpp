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
			pinMode(this->digitalPort[i]->getPin(), OUTPUT);
		}
		else
		{
			if (this->digitalPort[i]->isOnPullUp) {
				pinMode(this->digitalPort[i]->getPin(), INPUT_PULLUP);
			}
			else
			{
				pinMode(this->digitalPort[i]->getPin(), INPUT);
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


bool DeviceActivity::isThereAnyCustomMisureOnAlarm()
{
	float customMisureValue = getCustomMisureValue();
	//todo: add cicle for every digital ports.
	if (customMisureValue > this->digitalPort[0]->maxCustomMisureValue)
	{
		this->lastAlarmDescription = this->digitalPort[0]->customMisureValueDescription + " level HIGH :" + customMisureValue;
		return true;
	}
	if (customMisureValue < this->digitalPort[0]->minCustomMisureValue)
	{
		this->lastAlarmDescription = this->digitalPort[0]->customMisureValueDescription + " level LOW :" + customMisureValue;
		return true;
	}
	return false;
}

/// <summary>
/// check all ports to find an alarm
/// </summary>
/// <returns></returns>
/// 
/// 

bool DeviceActivity::isThereAnyDigitalPortOnAlarm()
{
	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		if (this->digitalPort[i]->isEnable)
		{

			if (this->digitalPort[i]->alarmOn == DigitalPort::AlarmOn::low && digitalRead(this->digitalPort[i]->getPin()) == LOW)
			{
				this->lastAlarmDescription = digitalPort[i]->getUid() + " level LOW";
				return true;

			}
			if (this->digitalPort[i]->alarmOn == DigitalPort::AlarmOn::high && digitalRead(this->digitalPort[i]->getPin()) == HIGH)
			{
				return true;
			}
		}
	}
	return false;
}

bool DeviceActivity::isThereAnyAnalogPortOnAlarm()
{
	for (int i = 0; i < this->analogPortsNumber; i++)
	{

		if (this->analogPort[i]->isEnable && this->analogPort[i]->maxVoltageAlarmValueIn != 0)
		{
			if (this->analogPort[i]->maxVoltageAlarmValueIn < (this->vref / 1023) * analogRead(this->analogPort[i]->getPin()))
			{
				this->lastAlarmDescription = analogPort[i]->getUid() + " level HIGH";
				return true;
			}

			if (this->analogPort[i]->minVoltageAlarmValueIn > (this->vref / 1023) * analogRead(this->analogPort[i]->getPin()))
			{
				this->lastAlarmDescription = analogPort[i]->getUid() + " level LOW";
				return true;
			}
		}
	}

	for (int i = 0; i < this->analogPortsNumber; i++)
	{
		//Serial.print("------------------------"); Serial.println(this->analogPort[i]->maxAlarmValueIn);
		if (this->analogPort[i]->isEnable && this->analogPort[i]->maxAlarmValueIn != 0)
		{
			//Serial.println("Entrato3");
			//Serial.println("Entrato2");

			if (this->analogPort[i]->maxAlarmValueIn < (analogRead(this->analogPort[i]->getPin())))
			{
				this->lastAlarmDescription = analogPort[i]->getUid() + " level HIGH:" + analogRead(this->analogPort[i]->getPin());
				return true;
			}

			if (this->analogPort[i]->minAlarmValueIn > (analogRead(this->analogPort[i]->getPin())))
			{
				this->lastAlarmDescription = analogPort[i]->getUid() + " level LOW";
				return true;
			}
		}
	}
	return false;
}

//bool DeviceActivity::isThereAnyPortOnAlarm()
//{
//	//Serial.println("Entrato");
//	for (int i = 0; i < this->digitalPortsNumber; i++)
//	{
//		if (this->digitalPort[i]->isEnable)
//		{
//
//			if (this->digitalPort[i]->alarmOn == DigitalPort::AlarmOn::low && digitalRead(this->digitalPort[i]->getPin()) == LOW)
//			{
//				this->lastAlarmDescription = digitalPort[i]->getUid() + " level LOW";
//				return true;
//
//			}
//			if (this->digitalPort[i]->alarmOn == DigitalPort::AlarmOn::high && digitalRead(this->digitalPort[i]->getPin()) == HIGH)
//			{
//				return true;
//			}
//		}
//	}
//
//	for (int i = 0; i < this->analogPortsNumber; i++)
//	{
//		
//		if (this->analogPort[i]->isEnable && this->analogPort[i]->maxVoltageAlarmValueIn != 0)
//		{
//			if (this->analogPort[i]->maxVoltageAlarmValueIn < (this->vref / 1023) * analogRead(this->analogPort[i]->getPin()))
//			{
//				this->lastAlarmDescription = analogPort[i]->getUid() + " level HIGH";
//				return true;
//			}
//
//			if (this->analogPort[i]->minVoltageAlarmValueIn > (this->vref / 1023) * analogRead(this->analogPort[i]->getPin()))
//			{
//				this->lastAlarmDescription = analogPort[i]->getUid() + " level LOW";
//				return true;
//			}
//		}
//	}
//
//	for (int i = 0; i < this->analogPortsNumber; i++)
//	{
//		//Serial.print("------------------------"); Serial.println(this->analogPort[i]->maxAlarmValueIn);
//		if (this->analogPort[i]->isEnable && this->analogPort[i]->maxAlarmValueIn != 0)
//		{
//			//Serial.println("Entrato3");
//			//Serial.println("Entrato2");
//			
//			if (this->analogPort[i]->maxAlarmValueIn < (analogRead(this->analogPort[i]->getPin())))
//			{
//				this->lastAlarmDescription = analogPort[i]->getUid() + " level HIGH";
//				return true;
//			}
//
//			if (this->analogPort[i]->minAlarmValueIn > (analogRead(this->analogPort[i]->getPin())))
//			{
//				this->lastAlarmDescription = analogPort[i]->getUid() + " level LOW";
//					return true;
//			}
//		}
//	}
//
//	return false;
//}

String DeviceActivity::getLastAlarmDescription(void)
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
		if (this->analogPort[i]->getUid() == analogPortName)
		{
			return (this->vref /1023) * analogRead(this->analogPort[i]->getPin());
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
		if (this->analogPort[i]->getUid() == analogPortName)
		{
			return analogRead(this->analogPort[i]->getPin());
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
		if (this->digitalPort[i]->getUid() == digitalPortName)
		{
			if (this->digitalPort[i]->direction == output)
			{
				digitalWrite(this->digitalPort[i]->getPin(), pinLevel);
				return true;
			}
			else
			{
				lastErrorDescription = this->digitalPort[i]->getUid() + String(" is not output mode");
				return false;
			}
		}
		
	}
}

uint8_t DeviceActivity::digitalReadByName(String digitalPortName)
{
	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		if (this->digitalPort[i]->getUid() == digitalPortName && this->digitalPort[i]->direction == input)
		{
			return digitalRead(this->digitalPort[i]->getPin());
		}
	}
}

float DeviceActivity::getUnitOfMisureValue(String analogPortName)
{
	float mathRelationship;
	for (int i = 0; i < this->analogPortsNumber; i++)
	{
		if (this->analogPort[i]->getUid() == analogPortName)
		{
			mathRelationship = this->analogPort[i]->unitOfMisureFullScale / this->vref;
			return ((this->vref / 1023) * analogRead(this->analogPort[i]->getPin())) * mathRelationship;
			/*else
			{
				lastError = this->analogPort[i]->uid + String(" is not output mode");
				return false;
			}*/
		}

	}
}

float  DeviceActivity::getCustomMisureValue() {
}




