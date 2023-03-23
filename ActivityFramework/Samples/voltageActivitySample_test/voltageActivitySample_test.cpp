#include "pch.h"
#include "CppUnitTest.h"
#include "src/extend.h"

#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/AvrMicroRepository.h"
#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/AnalogPort.h"
#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/AnalogPortSensor.h"
#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/VoltageActivity.h"
#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/DeviceActivity.h"
#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/DigitalPortSensor.h"
#include "/Repos/MicroControllerTeamProject/Libraries/ActivityFramework/DigitalPort.h"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace voltageActivitySampletest
{
	TEST_CLASS(voltageActivitySampletest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Mock<AvrMicroRepository> mockedAvrMicroRepository;
			AvrMicroRepository& avrMicroRepository = mockedAvrMicroRepository.get();
			

			AnalogPort listOfBatteryAnalogPorts[1];
			AnalogPortSensor analogSensor;
			VoltageActivity batteryVoltageActivity;

			listOfBatteryAnalogPorts[0] = AnalogPort("BA0", 14);
			listOfBatteryAnalogPorts[0].isEnable = true;
			listOfBatteryAnalogPorts[0].maxVoltageAlarmValueIn = 4.30f;
			listOfBatteryAnalogPorts[0].minVoltageAlarmValueIn = 3.25f;
			analogSensor = AnalogPortSensor("SB01", listOfBatteryAnalogPorts, sizeof(listOfBatteryAnalogPorts) / sizeof(listOfBatteryAnalogPorts[0]));
			

			When(Method(mockedAvrMicroRepository, begin_m)).AlwaysReturn();
			
			When(Method(mockedAvrMicroRepository, pinMode_m)).AlwaysReturn();

			When(Method(mockedAvrMicroRepository, analogVoltageRead_m)).AlwaysReturn(3.50f);

		

			batteryVoltageActivity = VoltageActivity(avrMicroRepository, analogSensor, 4.80f, commonsLayer::DEFAULT_m);

			float a = batteryVoltageActivity.getVoltage("BA0");

			Assert::AreEqual(3.50f,a);
		}
	};
}
