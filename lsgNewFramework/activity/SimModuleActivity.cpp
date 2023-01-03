#include "SimModuleActivity.h"
#include "..\repository\AvrMicroRepository.h"



SimModuleActivity::SimModuleActivity(DigitalPort** ports, uint8_t portsNumber) : DeviceActivity(ports, portsNumber) {
}

SimModuleActivity::SimModuleActivity() {
}

bool SimModuleActivity::makeCall(AvrMicroRepository& avrMicroRepository) {
	bool returnValue = false;
	avrMicroRepository.begin_m(this->_baud);
	char* bufferResponse;
	avrMicroRepository.clearBuffer_m();
	avrMicroRepository.print_m("atd"); avrMicroRepository.print_m(this->_prefixAndphoneNumber, true);
	if (avrMicroRepository.serial_available())
	{
		bufferResponse = avrMicroRepository.readString_m();
		char* findInResponse; 
		/*findInResponse = strstr(bufferResponse, "ERROR");
		if (findInResponse != NULL)
		{
			this->setLastErrorCode('E');
		}
		findInResponse = strstr(bufferResponse, "DIALTONE");
		if (findInResponse != NULL)
		{
			this->setLastErrorCode('D');
		}*/
		findInResponse = strstr(bufferResponse, "OK");
		if (findInResponse != NULL)
		{
			returnValue = true;
		}
		/*else
		{
			this->setLastErrorCode('N');
		}*/
//#if defined(VM_DEBUG)
//		avrMicroRepository.print_m("returned internal value : "); avrMicroRepository.print_m(bufferResponse, true);
//		avrMicroRepository.clearBuffer_m();
//#endif

//#if defined(VM_DEBUG)
//		avrMicroRepository.print_m("ram b:"); avrMicroRepository.print_m(avrMicroRepository.getFreeRam(), true);
//		avrMicroRepository.clearBuffer_m();
//#endif

		avrMicroRepository.free_m(bufferResponse);
		avrMicroRepository.delaym(2000);
	}
//#if defined(VM_DEBUG)
//	avrMicroRepository.print_m("ram a:"); avrMicroRepository.print_m(avrMicroRepository.getFreeRam(), true);
//	avrMicroRepository.clearBuffer_m();
//#endif
	return returnValue;
}

//void SimModuleActivity::makeCall(AvrMicroRepository& avrMicroRepository){
//	avrMicroRepository.begin_m(this->_baud);
//	char* bufferResponse;
//	avrMicroRepository.clearBuffer_m();
//	avrMicroRepository.print_m("atd");avrMicroRepository.println(this->_prefixAndphoneNumber);
//	if (avrMicroRepository.serial_available())
//	{
//		int bufferAddress = avrMicroRepository.readString_m(bufferResponse);
//		char* findInResponse = strstr(bufferResponse, "ERROR");
//		if (findInResponse != NULL)
//		{
//			avrMicroRepository.setLastErrorCode('E');
//		}
//#if defined(VM_DEBUG)
//		avrMicroRepository.print_m("returned internal value : "); avrMicroRepository.println(bufferResponse);
//		avrMicroRepository.clearBuffer_m();
//#endif
//
//#if defined(VM_DEBUG)
//		avrMicroRepository.print_m("free ram : "); avrMicroRepository.println(avrMicroRepository.getFreeRam());
//		avrMicroRepository.clearBuffer_m();
//#endif
//
//		avrMicroRepository.free_m(bufferResponse);
//		avrMicroRepository.delaym(2000);
//	}
//}

void SimModuleActivity::setPrefixAndphoneNumber(char* _prefixAndphoneNumber)
{
	this->_prefixAndphoneNumber = _prefixAndphoneNumber;
}

void SimModuleActivity::setBaud(long unsigned _baud)
{
	this->_baud = _baud;
}





