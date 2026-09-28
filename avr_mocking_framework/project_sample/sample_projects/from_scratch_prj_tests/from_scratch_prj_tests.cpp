#include "src/extend.h"
#include "pch.h"
#include "CppUnitTest.h"
#include "../from_scratch/GarageGateController_BL.h"
#include <mf_repository_AvrMicroRepository.h>
#include <mf_repository_HCSR04Repository.h>
#include <mf_activity_AnalogPortBActivity.h>
#include <mf_activity_AnalogPortCActivity.h>
#include <mf_activity_DigitalPortActivity.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace fromscratchprjtests
{
	TEST_CLASS(fromscratchprjtests){
		Mock<AvrMicroRepository> mockedAvrMicroRepository;
		Mock<HC_SR04_Repository> mockedHC_SR04_Repository;
		AvrMicroRepository& avrMicroRepository = mockedAvrMicroRepository.get();
		HC_SR04_Repository& hcsr04_repository = mockedHC_SR04_Repository.get();
		long unsigned fake_get_mill = 0;
	public:
		TEST_METHOD(TestMethod1){
			AnalogPortC thermistor1('A', 0, 60.00f, 1.00f);
			AnalogPortC thermistor2('A', 1, 60.00f, 1.00f);
			AnalogPortC* thermistor_list[2] = { &thermistor1 ,&thermistor2 };
			DigitalPort gate_rele('A', 11, mf::commons::commonsLayer::PortDirection::output);
			DigitalPort* gate_rele_list[1] = { &gate_rele };
			When(Method(mockedAvrMicroRepository, analogRead)).AlwaysReturn(512);
			When(Method(mockedAvrMicroRepository, get_vref)).AlwaysReturn(4.7);
			When(Method(mockedAvrMicroRepository, delay)).AlwaysReturn();
			When(Method(mockedAvrMicroRepository, pinMode)).AlwaysReturn();
			When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
			When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; });
			When(Method(mockedHC_SR04_Repository, measure_distance_cm)).AlwaysReturn(50);
			DigitalPortActivity gate_rele_activity(avrMicroRepository, gate_rele_list, 1);
			NTC3950thermistorActivity ntc3950thermistorActivity(avrMicroRepository, thermistor_list, 2, 100000);
			HCSR04Activity hcsr04Activity(hcsr04_repository, avrMicroRepository, 1, 100, 5000);
			GarageGateController_BL garageGateController_BL(avrMicroRepository, ntc3950thermistorActivity, hcsr04Activity, gate_rele_activity);
			while (fake_get_mill < 6000) {
				fake_get_mill += 1000;
				garageGateController_BL.open_the_door();
			}
			Assert::IsTrue(gate_rele.pin_value_for_tdd, L"Expected the gate rele to be enabled");
		}
	};
}
