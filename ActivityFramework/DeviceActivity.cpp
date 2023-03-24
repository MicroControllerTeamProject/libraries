#include "DeviceActivity.h"
#include <string.h>

#ifdef _DEBUG
#include <Arduino.h>
#endif

DeviceActivity::DeviceActivity(AvrMicroRepository& avrMicroRepository, DigitalPortSensor& digitalPortSensor) {
	this->avrMicroRepository = &avrMicroRepository;
	this->_digitalPortSensor = &digitalPortSensor;
	initializeDigitalPorts();
}

DeviceActivity::DeviceActivity(AvrMicroRepository& avrMicroRepository, AnalogPortSensor& analogPortSensor, float vref, commonsLayer::analogRefMode mode)
{
	this->_analogPortSensor = &analogPortSensor;
	this->_vref = vref;
	this->vrefMode = mode;
	this->avrMicroRepository = &avrMicroRepository;
	initializeAnalogPorts();
}


DeviceActivity::DeviceActivity() {
}

void DeviceActivity::initializeDigitalPorts()
{
	if (this->_digitalPortSensor != nullptr)
	{
		for (int i = 0; i < this->_digitalPortSensor->getDigitalPortsNumber(); i++)
		{
			DigitalPort digitalPort = this->_digitalPortSensor->getAllDigitalPorts()[i];
			/*if (digitalPort != nullptr)
			{*/
			if (digitalPort.direction == DigitalPort::output)
			{
				this->avrMicroRepository->pinMode_m(digitalPort.getPin(), DigitalPort::PortDirection::output/*OUTPUT*/);
			}
			else
			{
				if (digitalPort.isOnPullUp) {
					this->avrMicroRepository->pinMode_m(digitalPort.getPin(), (uint8_t)2/*INPUT_PULLUP*/);
				}
				else
				{
					this->avrMicroRepository->pinMode_m(digitalPort.getPin(), (uint8_t)0/*INPUT*/);
				}
			}
		}
	}
}

void DeviceActivity::initializeAnalogPorts() 
{
	this->avrMicroRepository->analogReferencem(this->vrefMode);
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


bool DeviceActivity::isDigitalPortOnAlarm()
{
	if (this->_digitalPortSensor != nullptr)
	{

		DigitalPort digitalPort = this->_digitalPortSensor->getAllDigitalPorts()[0];

		digitalPort.isOnError = false;
		if (digitalPort.isEnable && (digitalPort.direction == DigitalPort::input))
		{
			if (digitalPort.alarmTriggerOn == DigitalPort::AlarmOn::low && this->avrMicroRepository->digitalReadm(digitalPort.getPin()) == 0/*LOW*/)
			{
				return true;
			}
			if (digitalPort.alarmTriggerOn == DigitalPort::AlarmOn::high && this->avrMicroRepository->digitalReadm(digitalPort.getPin()) == 1/*HIGH*/)
			{
				return true;
			}
		}
	}
	return false;
}

bool DeviceActivity::isAnalogPortOnAlarm(char* analogPortUid)
{
	AnalogPortSensor* analogPortSensor = this->_analogPortSensor;

	if (analogPortSensor != nullptr)
	{
		for (int i = 0; i < analogPortSensor->getAnalogPortsNumber(); i++)
		{
			AnalogPort analogPort = analogPortSensor->getAllAnalogPorts()[i];

			if (analogPort.isEnable && analogPort.maxVoltageAlarmValueIn != 0 && (strcmp(analogPortUid, analogPort.getUid()) == 0))
			{
				float analogReadVoltageValue = this->avrMicroRepository->analogVoltageRead_m(analogPort.getPin(), this->getVref(), this->vrefMode);

				if (analogReadVoltageValue > analogPort.maxVoltageAlarmValueIn)
				{
					analogPort.isOnError = true;
					analogPort.analogVrefValue = analogReadVoltageValue;
					return true;
				}

				if (analogReadVoltageValue < analogPort.minVoltageAlarmValueIn)
				{
					analogPort.isOnError = true;
					analogPort.analogVrefValue = analogReadVoltageValue;
					return true;
				}
			}
			//cicle if you work with 0-1023 values.
			if (analogPort.isEnable && analogPort.maxAlarmValueIn != 0 && (strcmp(analogPortUid, analogPort.getUid()) == 0))
			{
				uint16_t analogReadValue = this->avrMicroRepository->analogReadm(analogPort.getPin());
				if (analogReadValue > analogPort.maxAlarmValueIn)
				{
					analogPort.isOnError = true;
					analogPort.digitalValue = analogReadValue;
					return true;
				}
				if (analogReadValue < analogPort.minAlarmValueIn)
				{
					analogPort.isOnError = true;
					analogPort.digitalValue = analogReadValue;
					return true;
				}
			}
			//}
		}
		////with multi ports
		//for (int i = 0; i < analogPortSensor->getAnalogPortsNumber(); i++)
		//{
		//	AnalogPort* analogPort = analogPortSensor->getAllAnalogPorts()[i];
		//	if (analogPort != nullptr)
		//	{
		//		if (analogPort->isEnable && analogPort->maxVoltageAlarmValueIn != 0 && (strcmp(analogPortUid, analogPort->getUid()) == 0))
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
		//		if (analogPort->isEnable && analogPort->maxAlarmValueIn != 0 && (strcmp(analogPortUid, analogPort->getUid()) == 0))
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
	return false;
}

float DeviceActivity::getAnalogPortVrefVoltage(char* analogPortUid) {

	AnalogPortSensor* analogPortSensor = this->_analogPortSensor;

	if (analogPortSensor != nullptr)
	{
		for (size_t i = 0; i < analogPortSensor->getAnalogPortsNumber(); i++)
		{
			AnalogPort analogPort = analogPortSensor->getAllAnalogPorts()[i];
			if (analogPort.isEnable && (strcmp(analogPortUid, analogPort.getUid()) == 0))
			{
				return (this->getVref() / 1024.00f) * this->avrMicroRepository->analogReadm(analogPort.getPin());
			}
		}
	}
	return 0;
}

float  DeviceActivity::getVref()
{
	return _vref;
}




