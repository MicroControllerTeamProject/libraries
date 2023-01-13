#include "DeviceActivity.h"
#include <string.h>


DeviceActivity::DeviceActivity(AvrMicroRepository& avrMicroRepository, IDigitalPorts* digitalPortSensor)
{
	initializeDigitalPorts(avrMicroRepository, digitalPortSensor);
}

DeviceActivity::DeviceActivity(AvrMicroRepository& avrMicroRepository,DigitalPort** digitalPort)
{
	this->digitalPort = digitalPort;
	this->digitalPortsNumber = sizeof(digitalPort) / sizeof(digitalPort[0]);
	this->avrMicroRepository = &avrMicroRepository;
	
	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		if (this->digitalPort[i]->direction == DigitalPort::output)
		{
			this->avrMicroRepository->pinMode_m(this->digitalPort[i]->getPin(), DigitalPort::output/*OUTPUT*/);
		}
		else
		{
			if (this->digitalPort[i]->isOnPullUp) {
				this->avrMicroRepository->pinMode_m(this->digitalPort[i]->getPin(), (uint8_t)2/*INPUT_PULLUP*/);
			}
			else
			{
				this->avrMicroRepository->pinMode_m(this->digitalPort[i]->getPin(), (uint8_t)0/*INPUT*/);
			}
		}
	}



}

DeviceActivity::DeviceActivity(AvrMicroRepository& avrMicroRepository, AnalogPort** analogPort,float vref, commonsLayer::analogRefMode mode, uint8_t analogPortsNumber)
{
	this->analogPort = analogPort;
	this->_analogPortsNumber = analogPortsNumber;
	this->_vref = vref;
	this->vrefMode = mode;
	this->avrMicroRepository = &avrMicroRepository;
}

DeviceActivity::DeviceActivity(){
}



void DeviceActivity::initializeDigitalPorts(AvrMicroRepository& avrMicroRepository, IDigitalPorts* digitalPortSensor)
{
	this->digitalPort = digitalPortSensor->getAllDigitalPorts();
	this->digitalPortsNumber = sizeof(digitalPort) / sizeof(digitalPort[0]);
	this->avrMicroRepository = &avrMicroRepository;

	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		if (this->digitalPort[i]->direction == DigitalPort::output)
		{
			this->avrMicroRepository->pinMode_m(this->digitalPort[i]->getPin(), DigitalPort::output/*OUTPUT*/);
		}
		else
		{
			if (this->digitalPort[i]->isOnPullUp) {
				this->avrMicroRepository->pinMode_m(this->digitalPort[i]->getPin(), (uint8_t)2/*INPUT_PULLUP*/);
			}
			else
			{
				this->avrMicroRepository->pinMode_m(this->digitalPort[i]->getPin(), (uint8_t)0/*INPUT*/);
			}
		}
	}
}

AnalogPort** DeviceActivity::getAllAnalogPorts()
{
	return this->analogPort;
}

DigitalPort** DeviceActivity::getAllDigitalPorts()
{
	return this->digitalPort;
}

uint8_t DeviceActivity::getAnalogPortsNumber()
{
	return this->_analogPortsNumber;
}

uint8_t DeviceActivity::getDigitalPortsNumber()
{
	return this->digitalPortsNumber;
}

//const char* DeviceActivity::getDeviceOnErrorUID()
//{
//	return this->deviceOnErrorUID;
//}

//bool DeviceActivity::isThereAnyCustomMisureOnAlarm()
//{
//	float customMisureValue = getCustomMisureValue();
//	//todo: add cicle for every digital ports.
//	if (customMisureValue > this->digitalPort[0]->maxCustomMisureValue)
//	{
//		this->lastAlarmDescription = this->digitalPort[0]->customMisureValueDescription + " level HIGH :" + customMisureValue;
//		return true;
//	}
//	if (customMisureValue < this->digitalPort[0]->minCustomMisureValue)
//	{
//		this->lastAlarmDescription = this->digitalPort[0]->customMisureValueDescription + " level LOW :" + customMisureValue;
//		return true;
//	}
//	return false;
//}
//
///// <summary>
///// check all ports to find an alarm
///// </summary>
///// <returns></returns>
///// 
///// 
//
//bool DeviceActivity::isThereAnyDigitalPortOnAlarm()
//{
//	for (int i = 0; i < this->digitalPortsNumber; i++)
//	{
//		if (this->digitalPort[i]->isEnable)
//		{
//
//			if (this->digitalPort[i]->alarmOn == DigitalPort::AlarmOn::low && _mainRepository.analogReadm(this->digitalPort[i]->getPin()) == LOW)
//			{
//				this->lastAlarmDescription = digitalPort[i]->getUid() + " level LOW";
//				return true;
//
//			}
//			if (this->digitalPort[i]->alarmOn == DigitalPort::AlarmOn::high && _mainRepository.analogReadm(this->digitalPort[i]->getPin()) == HIGH)
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}

bool DeviceActivity::isThereAnyAnalogPortOnAlarm()
{
	for (int i = 0; i < this->_analogPortsNumber; i++)
	{
		if (this->analogPort[i]->isEnable && this->analogPort[i]->maxVoltageAlarmValueIn != 0)
		{
			if (this->avrMicroRepository->analogVoltageRead_m(this->analogPort[i]->getPin(),this->getVref(),this->vrefMode) < this->analogPort[i]->maxVoltageAlarmValueIn)
			{			
				this->analogPort[i]->isOnError = true;
				this->analogPort[i]->analogVrefValue = this->avrMicroRepository->analogVoltageRead_m(this->analogPort[i]->getPin(), this->getVref(), this->vrefMode);
				return false;
			}

			if (this->avrMicroRepository->analogVoltageRead_m(this->analogPort[i]->getPin(), this->getVref(), this->vrefMode) > this->analogPort[i]->minVoltageAlarmValueIn)
			{
				this->analogPort[i]->isOnError = true;
				this->analogPort[i]->analogVrefValue = this->avrMicroRepository->analogVoltageRead_m(this->analogPort[i]->getPin(), this->getVref(), this->vrefMode);
				return false;
			} 
		}
	}
	for (int i = 0; i < this->_analogPortsNumber; i++)
	{
		//Serial.print_m("------------------------"); Serial.println(this->analogPort[i]->maxAlarmValueIn);
		if (this->analogPort[i]->isEnable && this->analogPort[i]->maxAlarmValueIn != 0)
		{
			
			//Serial.println("Entrato3");
			//Serial.println("Entrato2");
			if ((this->avrMicroRepository->analogReadm(this->analogPort[i]->getPin())) > this->analogPort[i]->maxAlarmValueIn )
			{
				this->analogPort[i]->isOnError = true;
				this->analogPort[i]->digitalValue = (this->avrMicroRepository->analogReadm(this->analogPort[i]->getPin()));
				return true;
			}
			if ((this->avrMicroRepository->analogReadm(this->analogPort[i]->getPin())) < this->analogPort[i]->minAlarmValueIn )
			{
				this->analogPort[i]->isOnError = true;
				this->analogPort[i]->digitalValue = (this->avrMicroRepository->analogReadm(this->analogPort[i]->getPin()));
				return true;
			}
		}
	}

	return false;
}

bool DeviceActivity::isThereAnyDigitalPortOnAlarm()
{
	bool returnValue = false;
	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		this->digitalPort[i]->isOnError = false;
		if (this->digitalPort[i]->isEnable && (this->digitalPort[i]->direction == DigitalPort::input))
		{
			if (this->digitalPort[i]->alarmTriggerOn == DigitalPort::AlarmOn::low && this->avrMicroRepository->digitalReadm(this->digitalPort[i]->getPin()) == 0/*LOW*/)
			{
				this->digitalPort[i]->isOnError = true;
				returnValue = true;
			}
			if (this->digitalPort[i]->alarmTriggerOn == DigitalPort::AlarmOn::high && this->avrMicroRepository->digitalReadm(this->digitalPort[i]->getPin()) == 1/*HIGH*/)
			{
				this->digitalPort[i]->isOnError = true;
				returnValue = true;
			}
		}
	}
	return returnValue;
}


bool DeviceActivity::isDigitalPortOnAlarm(char* portName)
{
	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		this->digitalPort[i]->isOnError = false;
		if (this->digitalPort[i]->isEnable && (this->digitalPort[i]->direction == DigitalPort::input))
		{
			if ((strcmp(portName, this->digitalPort[i]->getUid()) == 0) &&  this->digitalPort[i]->alarmTriggerOn == DigitalPort::AlarmOn::low && this->avrMicroRepository->digitalReadm(this->digitalPort[i]->getPin()) == 0/*LOW*/)
			{
				return true;
			}
			if ((strcmp(portName, this->digitalPort[i]->getUid()) == 0) && this->digitalPort[i]->alarmTriggerOn == DigitalPort::AlarmOn::high && this->avrMicroRepository->digitalReadm(this->digitalPort[i]->getPin()) == 1/*HIGH*/)
			{
				return true;
			}
		}
	}
	return false;
}

bool DeviceActivity::isDigitalPortOnAlarm(uint8_t pinNumber)
{
	for (int i = 0; i < this->digitalPortsNumber; i++)
	{
		this->digitalPort[i]->isOnError = false;
		if (this->digitalPort[i]->isEnable && (this->digitalPort[i]->direction == DigitalPort::input))
		{
			if ((this->digitalPort[i]->getPin() == pinNumber) &&  this->digitalPort[i]->alarmTriggerOn == DigitalPort::AlarmOn::low && this->avrMicroRepository->digitalReadm(this->digitalPort[i]->getPin()) == 0/*LOW*/)
			{
				return true;
			}
			if ((this->digitalPort[i]->getPin() == pinNumber) && this->digitalPort[i]->alarmTriggerOn == DigitalPort::AlarmOn::high && this->avrMicroRepository->digitalReadm(this->digitalPort[i]->getPin()) == 1/*HIGH*/)
			{
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
//		//Serial.print_m("------------------------"); Serial.println(this->analogPort[i]->maxAlarmValueIn);
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

//String DeviceActivity::getLastAlarmDescription(void)
//{
//	return this->lastAlarmDescription;
//}
//
//String DeviceActivity::getLastErrorDescription()
//{
//	return this->lastErrorDescription;
//}
//
//float DeviceActivity::analogReadVoltageByPin(uint8_t pin)
//{
//	for (int i = 0; i < this->_analogPortsNumber; i++)
//	{
//		if (this->analogPort[i]->getPin() == pin)
//		{
//			return this->_avrMicroRepository.analogVoltageRead_m(this->analogPort[i]->getPin(),this->_vref,this->vrefMode);
//			/*else
//			{
//				lastError = this->analogPort[i]->uid + String(" is not output mode");
//				return false;
//			}*/
//		}
//	}
//}
//
//int DeviceActivity::analogReadByName(String analogPortName)
//{
//	for (int i = 0; i < this->analogPortsNumber; i++)
//	{
//		if (this->analogPort[i]->getUid() == analogPortName)
//		{
//			return _mainRepository.analogReadm(this->analogPort[i]->getPin());
//			/*else
//			{
//				lastError = this->analogPort[i]->uid + String(" is not output mode");
//				return false;
//			}*/
//		}
//
//	}
//}
//
////bool DeviceActivity::digitalWriteByName(String digitalPortName,uint8_t pinLevel)
////{
////	for (int i = 0; i < this->digitalPortsNumber; i++)
////	{
////		if (this->digitalPort[i]->getUid() == digitalPortName)
////		{
////			if (this->digitalPort[i]->direction == output)
////			{
////				digitalWrite(this->digitalPort[i]->getPin(), pinLevel);
////				return true;
////			}
////			else
////			{
////				lastErrorDescription = this->digitalPort[i]->getUid() + String(" is not output mode");
////				return false;
////			}
////		}
////		
////	}
////}
////
//uint8_t DeviceActivity::digitalReadByName(String digitalPortName)
//{
//	for (int i = 0; i < this->digitalPortsNumber; i++)
//	{
//		if (this->digitalPort[i]->getUid() == digitalPortName && this->digitalPort[i]->direction == input)
//		{
//			return digitalRead(this->digitalPort[i]->getPin());
//		}
//	}
//}
//
//float DeviceActivity::getUnitOfMisureValue(String analogPortName)
//{
//	float mathRelationship;
//	for (int i = 0; i < this->analogPortsNumber; i++)
//	{
//		if (this->analogPort[i]->getUid() == analogPortName)
//		{
//			mathRelationship = this->analogPort[i]->unitOfMisureFullScale / this->vref;
//			return ((this->vref / 1023) * _mainRepository.analogReadm(this->analogPort[i]->getPin())) * mathRelationship;
//			/*else
//			{
//				lastError = this->analogPort[i]->uid + String(" is not output mode");
//				return false;
//			}*/
//		}
//
//	}
//}
//
//float  DeviceActivity::getCustomMisureValue() {
//}


float  DeviceActivity::getVref()
{
	return _vref;
}

//char DeviceActivity::getLastErrorCode()
//{
//	return this->_lastErrorCode;
//}
//
//void DeviceActivity::setLastErrorCode(char errorCode) {
//	this->_lastErrorCode = errorCode;
//}



