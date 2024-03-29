#include "DeviceActivity.h"
#include <string.h>

#ifdef _DEBUG
#include <Arduino.h>
#endif

DeviceActivity::DeviceActivity(AvrMicroRepository& avrMicroRepository, DigitalPortSensor** digitalPortSensors, uint8_t digitalPortSensorsNumber)
{
	this->avrMicroRepository = &avrMicroRepository;
	this->digitalPortSensors = digitalPortSensors;
	this->_digitalPortSensorNumber = digitalPortSensorsNumber;
	initializeDigitalPorts();
}

DeviceActivity::DeviceActivity(AvrMicroRepository& avrMicroRepository, AnalogPortSensor** analogPortSensor, float vref, commonsLayer::analogRefMode mode, uint8_t analogPortSensorsNumber)
{
	this->analogPortSensors = analogPortSensor;
	this->_analogPortsSensorNumber = analogPortSensorsNumber;
	this->_vref = vref;
	this->vrefMode = mode;
	this->avrMicroRepository = &avrMicroRepository;
}

DeviceActivity::DeviceActivity() {
}

void DeviceActivity::initializeDigitalPorts()
{
	for (int ii = 0; ii < this->_digitalPortSensorNumber; ii++) {
		DigitalPortSensor* digitalPortSensor = this->digitalPortSensors[ii];
		if (digitalPortSensor != nullptr)
		{
			for (int i = 0; i < digitalPortSensor->getDigitalPortsNumber(); i++)
			{
				DigitalPort* digitalPort = digitalPortSensor->getAllDigitalPorts()[i];
				if (digitalPort != nullptr)
				{
					if (digitalPort->direction == DigitalPort::output)
					{
						this->avrMicroRepository->pinMode_m(digitalPort->getPin(), DigitalPort::output/*OUTPUT*/);
					}
					else
					{
						if (digitalPort->isOnPullUp) {
							this->avrMicroRepository->pinMode_m(digitalPort->getPin(), (uint8_t)2/*INPUT_PULLUP*/);
						}
						else
						{
							this->avrMicroRepository->pinMode_m(digitalPort->getPin(), (uint8_t)0/*INPUT*/);
						}
					}

				}

			}
		}

	}

	//for (int i = 0; i < this->_digitalPortsNumber; i++)
	//{
	//	if (this->digitalPort[i]->direction == DigitalPort::output)
	//	{
	//		this->avrMicroRepository->pinMode_m(this->digitalPort[i]->getPin(), DigitalPort::output/*OUTPUT*/);
	//	}
	//	else
	//	{
	//		if (this->digitalPort[i]->isOnPullUp) {
	//			this->avrMicroRepository->pinMode_m(this->digitalPort[i]->getPin(), (uint8_t)2/*INPUT_PULLUP*/);
	//		}
	//		else
	//		{
	//			this->avrMicroRepository->pinMode_m(this->digitalPort[i]->getPin(), (uint8_t)0/*INPUT*/);
	//		}
	//	}
	//}
}

//AnalogPort** DeviceActivity::getAllAnalogPorts()
//{
//	return this->analogPort;
//}

//DigitalPort** DeviceActivity::getAllDigitalPorts()
//{
//	return this->digitalPort;
//}


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

//bool DeviceActivity::isThereAnyAnalogPortOnAlarm()
//{
//	for (int i = 0; i < this->_analogPortsNumber; i++)
//	{
//		if (this->analogPort[i]->isEnable && this->analogPort[i]->maxVoltageAlarmValueIn != 0)
//		{
//			if (this->avrMicroRepository->analogVoltageRead_m(this->analogPort[i]->getPin(), this->getVref(), this->vrefMode) < this->analogPort[i]->maxVoltageAlarmValueIn)
//			{
//				this->analogPort[i]->isOnError = true;
//				this->analogPort[i]->analogVrefValue = this->avrMicroRepository->analogVoltageRead_m(this->analogPort[i]->getPin(), this->getVref(), this->vrefMode);
//				return false;
//			}
//
//			if (this->avrMicroRepository->analogVoltageRead_m(this->analogPort[i]->getPin(), this->getVref(), this->vrefMode) > this->analogPort[i]->minVoltageAlarmValueIn)
//			{
//				this->analogPort[i]->isOnError = true;
//				this->analogPort[i]->analogVrefValue = this->avrMicroRepository->analogVoltageRead_m(this->analogPort[i]->getPin(), this->getVref(), this->vrefMode);
//				return false;
//			}
//		}
//	}
//	for (int i = 0; i < this->_analogPortsNumber; i++)
//	{
//		if (this->analogPort[i]->isEnable && this->analogPort[i]->maxAlarmValueIn != 0)
//		{
//			if ((this->avrMicroRepository->analogReadm(this->analogPort[i]->getPin())) > this->analogPort[i]->maxAlarmValueIn)
//			{
//				this->analogPort[i]->isOnError = true;
//				this->analogPort[i]->digitalValue = (this->avrMicroRepository->analogReadm(this->analogPort[i]->getPin()));
//				return true;
//			}
//			if ((this->avrMicroRepository->analogReadm(this->analogPort[i]->getPin())) < this->analogPort[i]->minAlarmValueIn)
//			{
//				this->analogPort[i]->isOnError = true;
//				this->analogPort[i]->digitalValue = (this->avrMicroRepository->analogReadm(this->analogPort[i]->getPin()));
//				return true;
//			}
//		}
//	}
//
//	return false;
//}


bool DeviceActivity::isDigitalPortOnAlarm(char* sensorUid)
{

	for (int ii = 0; ii < this->_digitalPortSensorNumber; ii++) {
		DigitalPortSensor* digitalPortSensor = this->digitalPortSensors[ii];
		if (digitalPortSensor != nullptr && (strcmp(sensorUid, digitalPortSensor->getUid()) == 0))
		{

			DigitalPort* digitalPort = digitalPortSensor->getAllDigitalPorts()[0];
			if (digitalPort != nullptr)
			{
				digitalPort->isOnError = false;
				if (digitalPort->isEnable && (digitalPort->direction == DigitalPort::input))
				{
					if (digitalPort->alarmTriggerOn == DigitalPort::AlarmOn::low && this->avrMicroRepository->digitalReadm(digitalPort->getPin()) == 0/*LOW*/)
					{
						return true;
					}
					if (digitalPort->alarmTriggerOn == DigitalPort::AlarmOn::high && this->avrMicroRepository->digitalReadm(digitalPort->getPin()) == 1/*HIGH*/)
					{
						return true;
					}
				}
			}
			//Logic on multi ports
			//for (int i = 0; i < digitalPortSensor->getDigitalPortsNumber(); i++)
			//{
			//	DigitalPort* digitalPort = digitalPortSensor->getAllDigitalPorts()[i];
			//	if (digitalPort != nullptr)
			//	{
			//		digitalPort->isOnError = false;
			//		if (digitalPort->isEnable && (digitalPort->direction == DigitalPort::input))
			//		{
			//			if ((strcmp(sensorUid, digitalPort->getUid()) == 0) && digitalPort->alarmTriggerOn == DigitalPort::AlarmOn::low && this->avrMicroRepository->digitalReadm(digitalPort->getPin()) == 0/*LOW*/)
			//			{
			//				return true;
			//			}
			//			if ((strcmp(sensorUid, digitalPort->getUid()) == 0) && digitalPort->alarmTriggerOn == DigitalPort::AlarmOn::high && this->avrMicroRepository->digitalReadm(digitalPort->getPin()) == 1/*HIGH*/)
			//			{
			//				return true;
			//			}
			//		}
			//	}
			//}
		}
	}
	return false;
}

bool DeviceActivity::isAnalogPortOnAlarm(char* sensorUid)
{
	for (int ii = 0; ii < this->_analogPortsSensorNumber; ii++) {
		AnalogPortSensor* analogPortSensor = this->analogPortSensors[ii];
		if (analogPortSensor != nullptr && (strcmp(sensorUid, analogPortSensor->getUid()) == 0))
		{
			AnalogPort* analogPort = analogPortSensor->getAllAnalogPorts()[0];
			if (analogPort != nullptr)
			{
				if (analogPort->isEnable && analogPort->maxVoltageAlarmValueIn != 0)
				{

					if (this->avrMicroRepository->analogVoltageRead_m(analogPort->getPin(), this->getVref(), this->vrefMode) > analogPort->maxVoltageAlarmValueIn)
					{
						analogPort->isOnError = true;
						analogPort->analogVrefValue = this->avrMicroRepository->analogVoltageRead_m(analogPort->getPin(), this->getVref(), this->vrefMode);
						return true;
					}

					if (this->avrMicroRepository->analogVoltageRead_m(analogPort->getPin(), this->getVref(), this->vrefMode) < analogPort->minVoltageAlarmValueIn)
					{
						analogPort->isOnError = true;
						analogPort->analogVrefValue = this->avrMicroRepository->analogVoltageRead_m(analogPort->getPin(), this->getVref(), this->vrefMode);
						return true;
					}
				}

				if (analogPort->isEnable && analogPort->maxAlarmValueIn != 0 )
				{
					if ((this->avrMicroRepository->analogReadm(analogPort->getPin())) > analogPort->maxAlarmValueIn)
					{
						analogPort->isOnError = true;
						analogPort->digitalValue = (this->avrMicroRepository->analogReadm(analogPort->getPin()));
						return true;
					}
					if ((this->avrMicroRepository->analogReadm(analogPort->getPin())) < analogPort->minAlarmValueIn)
					{
						analogPort->isOnError = true;
						analogPort->digitalValue = (this->avrMicroRepository->analogReadm(analogPort->getPin()));
						return true;
					}
				}
			}
			////with multi ports
			//for (int i = 0; i < analogPortSensor->getAnalogPortsNumber(); i++)
			//{
			//	AnalogPort* analogPort = analogPortSensor->getAllAnalogPorts()[i];
			//	if (analogPort != nullptr)
			//	{
			//		if (analogPort->isEnable && analogPort->maxVoltageAlarmValueIn != 0 && (strcmp(sensorUid, analogPort->getUid()) == 0))
			//		{
			//			if (this->avrMicroRepository->analogVoltageRead_m(analogPort->getPin(), this->getVref(), this->vrefMode) > analogPort->maxVoltageAlarmValueIn)
			//			{
			//				analogPort->isOnError = true;
			//				analogPort->analogVrefValue = this->avrMicroRepository->analogVoltageRead_m(analogPort->getPin(), this->getVref(), this->vrefMode);
			//				return true;
			//			}
			//			if (this->avrMicroRepository->analogVoltageRead_m(analogPort->getPin(), this->getVref(), this->vrefMode) < analogPort->minVoltageAlarmValueIn)
			//			{
			//				analogPort->isOnError = true;
			//				analogPort->analogVrefValue = this->avrMicroRepository->analogVoltageRead_m(analogPort->getPin(), this->getVref(), this->vrefMode);
			//				return true;
			//			}
			//		}
			//		if (analogPort->isEnable && analogPort->maxAlarmValueIn != 0 && (strcmp(sensorUid, analogPort->getUid()) == 0))
			//		{
			//			if ((this->avrMicroRepository->analogReadm(analogPort->getPin())) > analogPort->maxAlarmValueIn)
			//			{
			//				analogPort->isOnError = true;
			//				analogPort->digitalValue = (this->avrMicroRepository->analogReadm(analogPort->getPin()));
			//				return true;
			//			}
			//			if ((this->avrMicroRepository->analogReadm(analogPort->getPin())) < analogPort->minAlarmValueIn)
			//			{
			//				analogPort->isOnError = true;
			//				analogPort->digitalValue = (this->avrMicroRepository->analogReadm(analogPort->getPin()));
			//				return true;
			//			}
			//		}
			//	}
			//}
		}
	}
	return false;
}

float DeviceActivity::getAnalogPortVrefVoltage(char* sensorUid) {
	for (int ii = 0; ii < this->_analogPortsSensorNumber; ii++) {
		AnalogPortSensor* analogPortSensor = this->analogPortSensors[ii];
		if (analogPortSensor != nullptr && (strcmp(sensorUid, analogPortSensor->getUid()) == 0))
		{
			AnalogPort* analogPort = analogPortSensor->getAllAnalogPorts()[0];

			if (analogPort != nullptr)
			{
				if (analogPort->isEnable)
				{
					return this->avrMicroRepository->analogVoltageRead_m(analogPort->getPin(), this->getVref(), this->vrefMode);
				}
			}

			////Multi ports
			//for (int i = 0; i < analogPortSensor->getAnalogPortsNumber(); i++)
			//{
			//	AnalogPort* analogPort = analogPortSensor->getAllAnalogPorts()[i];
			//	if (analogPort != nullptr)
			//	{
			//		if (analogPort->isEnable && (strcmp(sensorUid, analogPort->getUid()) == 0))
			//		{
			//			return this->avrMicroRepository->analogVoltageRead_m(analogPort->getPin(), this->getVref(), this->vrefMode);
			//		}
			//	}
			//}
		}
	}
	return 0;
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



