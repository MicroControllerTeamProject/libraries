#include "pch.h"
#include "CppUnitTest.h"
#include "src/extend.h"

#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/SimModuleActivity.h"
//#include "/Repos/MicroControllerTeamProject/ActivityFramework/activity/DeviceActivity.h"
//#include "/Repos/MicroControllerTeamProject/ActivityFramework/repository/AvrMicroRepository.h"
//#include "/Repos/MicroControllerTeamProject/ActivityFramework/model/DigitalPort.h"
//#include "/Repos/MicroControllerTeamProject/ActivityFramework/objectsSensor/SimModuleDevice.h"
#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/AvrMicroRepository.h"
#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/SoftwareSerialRepository.h"
//#include "/Repos/MicroControllerTeamProject/ActivityFramework/interfaces/InterfaceSerialRepository.h"
#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/SimProgMemRepository.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SerialFrameworkSampleTest
{
	TEST_CLASS(SerialFrameworkSampleTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Mock<SimProgMemRepository> mockedSimProgMemRepository;
			SimProgMemRepository& simProgMemRepository = mockedSimProgMemRepository.get();
			Mock<SoftwareSerialRepository> mockedSoftwareSerialRepository;
			SoftwareSerialRepository& softwareSerialRepository = mockedSoftwareSerialRepository.get();
			Mock<AvrMicroRepository> mockedAvrMicroRepository;
			AvrMicroRepository& avrMicroRepository = mockedAvrMicroRepository.get();

			DigitalPort listOfPortsForSimModule[1];

			listOfPortsForSimModule[0] = DigitalPort("T", 5);

			listOfPortsForSimModule[0].direction = DigitalPort::PortDirection::output;

			SimModuleDevice simModuleDevice;

			simModuleDevice = SimModuleDevice("Sim01", listOfPortsForSimModule,1);

			simModuleDevice.init("+39", "3202445649;");

			//present in the constructor
			When(Method(mockedSoftwareSerialRepository, begin_m)).AlwaysReturn();

			//present in the constructor
			When(Method(mockedAvrMicroRepository, begin_m)).AlwaysReturn();

			//present in base class DeviceActivity on SimModuleActivity 
			When(Method(mockedAvrMicroRepository, pinMode_m)).AlwaysReturn();

			//present in simModuleActivity.isSmsOnBuffer
			When(Method(mockedSimProgMemRepository, getSmsToFind)).AlwaysReturn("Md");

			SimModuleActivity simModuleActivity = SimModuleActivity(softwareSerialRepository, simProgMemRepository, avrMicroRepository, simModuleDevice);

			bool returnValue = simModuleActivity.isSmsOnBuffer("+CMGR:\"REC READ\",\"+393202445649\",,\"07/07/05,09:56:03+08\"Md\r", 0, 5);
			
			Assert::AreEqual(true, returnValue);
		}
	};
}
