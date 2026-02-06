#include "pch.h"
#include "src/extend.h"
#include "CppUnitTest.h"
#include "../12VoltsBatteriesRack/src/model/DeMuxPlexerEntity.h"
#include "../12VoltsBatteriesRack/src/business/ControlUnit_BL.h"
#include <mf_repository_AvrMicroRepository.h>
#include <mf_commons_commonsLayer.h>
#include <mf_model_AnalogPortB.h>
#include <mf_model_AnalogPortD.h>
#include <mf_activity_AnalogPortDActivity.h>
#include <mf_activity_DigitalPortActivity.h>
#include <mf_activity_NTC3950thermistorActivity.h>
#include <mf_activity_AnalogPortCActivity.h>
#include <mf_activity_AnalogPortBActivity.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace MockProjectSampleTest {
	TEST_CLASS(MockProjectSampleTest) {
		Mock<AvrMicroRepository> mockedAvrMicroRepository;
		AvrMicroRepository& avrMicroRepository = mockedAvrMicroRepository.get();
		long unsigned fake_get_mill = 0;
		//uint8_t pin_temperature_battery_group_01 = 3;
		//uint8_t pin_smoke_check_battery_group_01 = 9; 
		//uint8_t pin_rele_group_01 = 10; // Example pin number for the relay
		//uint8_t rele_pin_g2_1 = 11; // Example pin number for the relay
		//uint8_t current_port_g1_pin = 1; // Example pin number for the relay
		//uint8_t current_port_g2_pin = 2; // Example pin number for the relay
		//AnalogPort temperature_port_01 = AnalogPort("T01", "G01", pin_temperature_battery_group_01, 60.00f,2.00f);
		//AnalogPort smoke_port_01 = AnalogPort("S01","G01", pin_smoke_check_battery_group_01, (uint16_t)540, (uint16_t)50);
		//DigitalPort rele_port_g1 = DigitalPort("R01","G01", pin_rele_group_01, commonsLayer::PortDirection::output);
		//DigitalPort rele_port_g2 = DigitalPort("R02","G02", rele_pin_g2_1, commonsLayer::PortDirection::output);
		//AnalogPort current_port_01 = AnalogPort("C01","G01", current_port_g1_pin, 20, 10, 2, true);
		//AnalogPort current_port_02 = AnalogPort("C02", "G02", current_port_g2_pin, 20, 9, 2, true);
		//long unsigned fake_get_mill = 0;
public:
	TEST_METHOD_INITIALIZE(Initialize) {
		/*smoke_port_01.analogPorttype = commonsLayer::digital;
		current_port_01.analogPorttype = commonsLayer::custom_misure;
		current_port_02.analogPorttype = commonsLayer::custom_misure;
		temperature_port_01.analogPorttype = commonsLayer::custom_misure;
		temperature_port_01.set_alarm_if_above_threshold_for_seconds = 5;
		current_port_01.set_alarm_if_above_threshold_for_seconds = 5;
		current_port_02.set_alarm_if_above_threshold_for_seconds = 5;
		current_port_01.set_alarm_if_under_threshold_for_seconds = 5;
		current_port_02.set_alarm_if_under_threshold_for_seconds = 5;*/
	}
	TEST_METHOD_CLEANUP(Cleanup) {
	}
	TEST_METHOD(test_for_digital) {
		When(Method(mockedAvrMicroRepository, pinMode)).AlwaysReturn();
		When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
		AnalogPortD analogPortForDigitalMeasure1('A', 2, 400, 100);
		AnalogPortD analogPortForDigitalMeasure2('B', 3, 400, 100);
		AnalogPortD analogPortForDigitalMeasure3('C', 4, 700, 100);
		analogPortForDigitalMeasure1.set_alarm_if_above_threshold_for_seconds = 50;
		AnalogPortD* analogPortForDigitalMeasureList[] = { &analogPortForDigitalMeasure1, &analogPortForDigitalMeasure2 , &analogPortForDigitalMeasure3 };
		AnalogPortDActivity analogPortDigitalActivity(avrMicroRepository, analogPortForDigitalMeasureList, 3);
		When(Method(mockedAvrMicroRepository, analogRead).Using(2)).AlwaysReturn(512);
		When(Method(mockedAvrMicroRepository, analogRead).Using(3)).AlwaysReturn(512);
		When(Method(mockedAvrMicroRepository, analogRead).Using(4)).AlwaysReturn(680);
		When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; });
		bool any_port_is_on_alarm = false;
		while (fake_get_mill < 7000) {
			any_port_is_on_alarm = false;
			fake_get_mill += 1000;
			analogPortDigitalActivity.analog_read_for_all_ports();
			any_port_is_on_alarm = analogPortDigitalActivity.is_any_port_out_of_range();
			if (any_port_is_on_alarm) {
				for each(AnalogPortD * analogPortD in analogPortForDigitalMeasureList) {
					if (analogPortD->is_onAlarm && analogPortD->is_time_above_threshold_elapsed && analogPortD->is_enabled) {
						analogPortD->is_enabled = false;
						//group_to_disable = analogPortc->get_group_id();
						//turn off rele where group = group
					}
				}
			}
		}
		Assert::IsTrue(analogPortForDigitalMeasure1.is_enabled, L"Expected group A to disable");
		Assert::IsFalse(analogPortForDigitalMeasure2.is_enabled, L"Expected group B to disable");

		/*Assert::IsTrue(result == false, L"Expected the current to be above the threshold but time is under 5 seconds.");
		Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::high, L"Expected the relay g1 to be turned off (LOW).");*/
	}
	TEST_METHOD(test_for_analog_read_thermistors) {
		When(Method(mockedAvrMicroRepository, pinMode)).AlwaysReturn();
		When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
		When(Method(mockedAvrMicroRepository, get_vref)).AlwaysReturn(4.70f);
		When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; });
		When(Method(mockedAvrMicroRepository, delay)).AlwaysReturn();
		DigitalPort relay_01('A', 11, mf::commons::commonsLayer::PortDirection::output);
		AnalogPortC thermistor1('A', 0, 60.00f, 1.00f);
		AnalogPortC current1('A', 10, 20.00f, 2.00f, 0.50f,true);
		AnalogPortC current2('B', 11, 20.00f, 2.00f, 0.50f, true);
		AnalogPortC* current_list[2] = { &current1,&current2};
		AnalogPortC* thermistor_list[1] = { &thermistor1 };
		DigitalPort* relay_list[1] = { &relay_01};
		AnalogPortCActivity currentActivity(avrMicroRepository, current_list, 1);
		DigitalPortActivity relayActivity(avrMicroRepository, relay_list, 1);
		NTC3950thermistorActivity ntc_3950thermistorActivity(avrMicroRepository, thermistor_list, 1, 100000.00f);
		std::vector<int> thermistor_values{ 100/*,500,500,500,500,500*/ };
		std::vector<int> current_values{ 640,600,600,600,600,800 };
		size_t i = 0;
		AppConfig appConfig;
		ControlUnit_BL controlUnit_BL(avrMicroRepository, appConfig, ntc_3950thermistorActivity, relayActivity, currentActivity);
		bool any_port_is_on_alarm = false;
		controlUnit_BL.turn_on_off_all_relays(true);
		When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return current_values[(i++) % current_values.size()]; });
		controlUnit_BL.calculate_current_sensors_offset(1);
		while (fake_get_mill < 7000) {
			i = 0;
			fake_get_mill += 1000;
			/*When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return thermistor_values[(i++) % thermistor_values.size()]; });
			any_port_is_on_alarm = controlUnit_BL.disable_relays_where_thermistor_is_on_alarm();*/
			When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return current_values[(i++) % current_values.size()]; });
			any_port_is_on_alarm = controlUnit_BL.disable_relays_where_current_is_on_alarm();
		}
		Assert::IsTrue(!relay_01.pin_value, L"Expected relay_01 to be disabled");
		/*Assert::IsTrue(relay_02.pin_value, L"Expected relay_02 to be enabled");
		Assert::IsTrue(relay_04.pin_value, L"Expected relay_04 to be enabled");
		Assert::IsTrue(relay_05.pin_value, L"Expected relay_05 to be disabled");
		Assert::IsTrue(!relay_06.pin_value, L"Expected relay_06 to be disabled");*/
	}
	//		analogPortDigitalActivity.read_and_set_digital_value((AnalogPortB**)analogPortForDigitalMeasureList);
	//		any_port_is_on_alarm = analogPortDigitalActivity.is_any_port_out_of_range();
	//		if (any_port_is_on_alarm) {
	//			for each(AnalogPortB * analogPortB in analogPortForDigitalMeasureList) {
	//				if (analogPortB->is_onAlarm && analogPortB->is_time_above_threshold_elapsed && analogPortB->is_enabled) {
	//					analogPortB->is_enabled = false;
	//					//group_to_disable = analogPortc->get_group_id();
	//					//turn off rele where group = group
	//				}
	//			}
	//		}
	//	}
	//	controlUnit_BL.is_thermistor_port_values_out_of_range();

	//}
	//TEST_METHOD(is_over_temperature_but_alarm_time_not_elapsed) {
	//	AnalogPort* analog_sensor_list[] = { &temperature_port_01 };
	//	DigitalPort* digital_sensor_list[] = { &rele_port_g1 };
	//	NTC3950thermistorActivity analog_sensors_activity = NTC3950thermistorActivity(avrMicroRepository, analog_sensor_list, 1,100000.00f);
	//	DigitalPortActivity digital_sensors_activity = DigitalPortActivity(avrMicroRepository, digital_sensor_list, 1);
	//	When(Method(mockedAvrMicroRepository, analogRead).Using(pin_temperature_battery_group_01)).AlwaysReturn(300);
	//	When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
	//	When(Method(mockedAvrMicroRepository, get_vref)).AlwaysReturn(5.00f);
	//	When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; }); // dichiarata UNA VOLTA
	//	Charge_Battery_BL charge_Battery_BL = Charge_Battery_BL(analog_sensors_activity, digital_sensors_activity);
	//	charge_Battery_BL.start_charging();
	//	Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::high, L"Expected the relay to be turned on (HIGH).");
	//	bool result = false;
	//	while (fake_get_mill < 4000) {
	//		fake_get_mill += 1000;
	//		result = charge_Battery_BL.turn_off_rele_where_current_above_threshold();
	//	}
	//	Assert::IsTrue(result == false, L"Expected the current to be above the threshold but time is under 5 seconds.");
	//	Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::high, L"Expected the relay g1 to be turned off (LOW).");
	//}
	//TEST_METHOD(is_overcurrent_but_alarm_time_not_elapsed) {
	//	AnalogPort* analog_sensor_list[] = { &current_port_01,&current_port_02 , &smoke_port_01};
	//	DigitalPort* digital_sensor_list[] = { &rele_port_g1,&rele_port_g2};
	//	AnalogPortActivity analog_sensors_activity = AnalogPortActivity(avrMicroRepository, analog_sensor_list, 3);
	//	DigitalPortActivity digital_sensors_activity = DigitalPortActivity(avrMicroRepository, digital_sensor_list, 2);
	//	Charge_Battery_BL charge_Battery_BL = Charge_Battery_BL(analog_sensors_activity, digital_sensors_activity);
	//	When(Method(mockedAvrMicroRepository, analogRead).Using(current_port_g1_pin)).AlwaysReturn(800);
	//	When(Method(mockedAvrMicroRepository, analogRead).Using(current_port_g2_pin)).AlwaysReturn(800);
	//	When(Method(mockedAvrMicroRepository, analogRead).Using(pin_smoke_check_battery_group_01)).AlwaysReturn(800);
	//	When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
	//	When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; }); // dichiarata UNA VOLTA
	//	charge_Battery_BL.start_charging();
	//	Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::high, L"Expected the relay to be turned on (HIGH).");
	//	Assert::IsTrue(rele_port_g2.pin_value == commonsLayer::high, L"Expected the relay to be turned on (HIGH).");
	//	bool result = false;
	//	while(fake_get_mill < 4000){
	//		fake_get_mill += 1000;
	//		result = charge_Battery_BL.turn_off_rele_where_current_above_threshold();
	//	}
	//	Assert::IsTrue(result == false, L"Expected the current to be above the threshold but time is under 5 seconds.");
	//	Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::high, L"Expected the relay g1 to be turned off (LOW).");
	//	Assert::IsTrue(rele_port_g2.pin_value == commonsLayer::high, L"Expected the relay g2 to be turned on (HIGH).");
	//}
	//TEST_METHOD(is_overcurrent_and_alarm_time_elapsed) {
	//	AnalogPort* analogPortList[] = { &current_port_01,&current_port_02 };
	//	DigitalPort* digitalPortList[] = { &rele_port_g1,&rele_port_g2 };
	//	When(Method(mockedAvrMicroRepository, analogRead).Using(current_port_g1_pin)).AlwaysReturn(800);
	//	When(Method(mockedAvrMicroRepository, analogRead).Using(current_port_g2_pin)).AlwaysReturn(800);
	//	When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
	//	When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; }); // dichiarata UNA VOLTA
	//	AnalogPortActivity currentActivity = AnalogPortActivity(avrMicroRepository, analogPortList, 2);
	//	DigitalPortActivity releActivity = DigitalPortActivity(avrMicroRepository, digitalPortList, 2);
	//	Charge_Battery_BL charge_Battery_BL = Charge_Battery_BL(currentActivity, releActivity);
	//	charge_Battery_BL.start_charging();
	//	Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::high, L"Expected the relay to be turned on (HIGH).");
	//	Assert::IsTrue(rele_port_g2.pin_value == commonsLayer::high, L"Expected the relay to be turned on (HIGH).");
	//	bool result = false;
	//	while (fake_get_mill < 7000) {
	//		fake_get_mill += 1000;
	//		result = charge_Battery_BL.turn_off_rele_where_current_above_threshold();
	//	}
	//	Assert::IsTrue(result == true, L"Expected the current to be above the threshold but time is under 5 seconds.");
	//	Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::low, L"Expected the relay g1 to be turned off (LOW).");
	//	Assert::IsTrue(rele_port_g2.pin_value == commonsLayer::low, L"Expected the relay g2 to be turned on (HIGH).");
	//}
	//TEST_METHOD(is_undercurrent_but_alarm_time_not_elapsed) {
	//	AnalogPort* analogPortList[] = { &current_port_01,&current_port_02 };
	//	DigitalPort* digitalPortList[] = { &rele_port_g1,&rele_port_g2 };
	//	When(Method(mockedAvrMicroRepository, analogRead).Using(current_port_g1_pin)).AlwaysReturn(512);
	//	When(Method(mockedAvrMicroRepository, analogRead).Using(current_port_g2_pin)).AlwaysReturn(512);
	//	When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
	//	When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; }); // dichiarata UNA VOLTA
	//	AnalogPortActivity currentActivity = AnalogPortActivity(avrMicroRepository, analogPortList, 2);
	//	DigitalPortActivity releActivity = DigitalPortActivity(avrMicroRepository, digitalPortList, 2);
	//	Charge_Battery_BL charge_Battery_BL = Charge_Battery_BL(currentActivity, releActivity);
	//	charge_Battery_BL.start_charging();
	//	Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::high, L"Expected the relay to be turned on (HIGH).");
	//	Assert::IsTrue(rele_port_g2.pin_value == commonsLayer::high, L"Expected the relay to be turned on (HIGH).");
	//	bool result = false;
	//	while (fake_get_mill < 4000) {
	//		fake_get_mill += 1000;
	//		result = charge_Battery_BL.turn_off_rele_where_current_under_threshold();
	//	}
	//	Assert::IsTrue(result == false, L"Expected the current to be above the threshold but time is under 5 seconds.");
	//	Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::high, L"Expected the relay g1 to be turned off (LOW).");
	//	Assert::IsTrue(rele_port_g2.pin_value == commonsLayer::high, L"Expected the relay g2 to be turned on (HIGH).");
	//}
	//TEST_METHOD(is_undercurrent_and_alarm_time_elapsed) {
	///*	current_port_01.set_alarm_if_under_threshold_for_seconds = 5;
	//	current_port_02.set_alarm_if_under_threshold_for_seconds = 5;*/
	//	AnalogPort* analogPortList[] = { &current_port_01,&current_port_02 };
	//	DigitalPort* digitalPortList[] = { &rele_port_g1,&rele_port_g2 };
	//	When(Method(mockedAvrMicroRepository, analogRead).Using(current_port_g1_pin)).AlwaysReturn(512);
	//	When(Method(mockedAvrMicroRepository, analogRead).Using(current_port_g2_pin)).AlwaysReturn(512);
	//	When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
	//	When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; }); // dichiarata UNA VOLTA
	//	AnalogPortActivity currentActivity = AnalogPortActivity(avrMicroRepository, analogPortList, 2);
	//	DigitalPortActivity releActivity = DigitalPortActivity(avrMicroRepository, digitalPortList, 2);
	//	Charge_Battery_BL charge_Battery_BL = Charge_Battery_BL(currentActivity, releActivity);
	//	charge_Battery_BL.start_charging();
	//	Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::high, L"Expected the relay to be turned on (HIGH).");
	//	Assert::IsTrue(rele_port_g2.pin_value == commonsLayer::high, L"Expected the relay to be turned on (HIGH).");
	//	bool result = false;
	//	while (fake_get_mill < 7000) {
	//		fake_get_mill += 1000;
	//		result = charge_Battery_BL.turn_off_rele_where_current_under_threshold();
	//	}
	//	Assert::IsTrue(result == true, L"Expected the current to be above the threshold but time is under 5 seconds.");
	//	Assert::IsTrue(rele_port_g1.pin_value == commonsLayer::low, L"Expected the relay g1 to be turned off (LOW).");
	//	Assert::IsTrue(rele_port_g2.pin_value == commonsLayer::low, L"Expected the relay g2 to be turned on (HIGH).");
	//}
	//TEST_METHOD(NTC3950_test) {
	//	MultiplexerActivity multiplexerActivity = MultiplexerActivity(avrMicroRepository, 1, 2, 3, 4);
	//	When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
	//	multiplexerActivity.set_multiplexer(2);
	//}
	//	TEST_METHOD(Test_open_garage_door_human_yes_smoke_no) {
	//		Mock<AvrMicroRepository> mockedAvrMicroRepository;
	//		AvrMicroRepository& avrMicroRepository = mockedAvrMicroRepository.get();
	//		DigitalPort pir_sensor_left = DigitalPort("Pi0", pin_pir_left, commonsLayer::AlarmTriggerOn::high, commonsLayer::PortDirection::input);
	//		DigitalPort pir_sensor_right = DigitalPort("Pi1", pin_pir_right, commonsLayer::AlarmTriggerOn::high, commonsLayer::PortDirection::input);
	//		DigitalPort* digitalPortList[] = { &pir_sensor_left ,&pir_sensor_right };
	//		AnalogPort smoke_sensor_left = AnalogPort("Sm1", pin_smoke_left);
	//		AnalogPort smoke_sensor_right = AnalogPort("Sm2", pin_smoke_right);
	//		smoke_sensor_left.min_digital_alarm_value_in = 100;
	//		smoke_sensor_left.max_digital_alarm_value_in = 900;
	//		smoke_sensor_right.min_digital_alarm_value_in = 100;
	//		smoke_sensor_right.max_digital_alarm_value_in = 900;
	//		AnalogPort* analogPortList[] = { &smoke_sensor_left, &smoke_sensor_right };
	//		DigitalPortActivity pirActivity = DigitalPortActivity(digitalPortList, 2);
	//		AnalogPortActivity smokeActivity = AnalogPortActivity(analogPortList, 2);
	//#pragma region	whenMethodes
	//		When(Method(mockedAvrMicroRepository, analogReference)).AlwaysReturn();
	//		When(Method(mockedAvrMicroRepository, delay)).AlwaysReturn();
	//		When(Method(mockedAvrMicroRepository, digitalRead).Using(pin_pir_left)).AlwaysReturn(1);
	//		When(Method(mockedAvrMicroRepository, digitalRead).Using(pin_pir_right)).AlwaysReturn(0);
	//		When(Method(mockedAvrMicroRepository, analogRead).Using(pin_smoke_left)).AlwaysReturn(100);
	//		When(Method(mockedAvrMicroRepository, analogRead).Using(pin_smoke_right)).AlwaysReturn(500);
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(const char*))).AlwaysDo([](const char* data) { (void)data; });
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(float))).AlwaysDo([](float data) { (void)data;});
	//		/*When(OverloadedMethod(mockedAvrMicroRepository, print, void(int, bool))).AlwaysDo([](int data, bool nl) { (void)data; (void)nl; });
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(uint8_t, bool))).AlwaysDo([](uint8_t data, bool nl) { (void)data; (void)nl; });*/
	//#pragma endregion
	//		Garage_Business_Layer garage_Business_Layer = Garage_Business_Layer();
	//		bool isDoorOpened = garage_Business_Layer.can_open_the_door(avrMicroRepository, pirActivity, smokeActivity);
	//		Assert::IsTrue(isDoorOpened, L"Expected the door to be opened when both smoke sensors are inactive (0).");
	//	}
	//	TEST_METHOD(Test_open_garage_door_human_no_smoke_yes) {
	//		Mock<AvrMicroRepository> mockedAvrMicroRepository;
	//		AvrMicroRepository& avrMicroRepository = mockedAvrMicroRepository.get();
	//		DigitalPort pir_sensor_left = DigitalPort("Pi0", pin_pir_left, DigitalPort::AlarmTriggerOn::high, DigitalPort::PortDirection::input);
	//		DigitalPort pir_sensor_right = DigitalPort("Pi1", pin_pir_right, DigitalPort::AlarmTriggerOn::high, DigitalPort::PortDirection::input);
	//		DigitalPort* digitalPortList[] = { &pir_sensor_left ,&pir_sensor_right };
	//		AnalogPort smoke_sensor_left = AnalogPort("Sm1", pin_smoke_left);
	//		AnalogPort smoke_sensor_right = AnalogPort("Sm2", pin_smoke_right);
	//		smoke_sensor_left.min_digital_alarm_value_in = 100;
	//		smoke_sensor_left.max_digital_alarm_value_in = 900;
	//		smoke_sensor_right.min_digital_alarm_value_in = 100;
	//		smoke_sensor_right.max_digital_alarm_value_in = 900;
	//		AnalogPort* analogPortList[] = { &smoke_sensor_left, &smoke_sensor_right };
	//		DigitalPortActivity pirActivity = DigitalPortActivity(digitalPortList, 2);
	//		AnalogPortActivity smokeActivity = AnalogPortActivity(analogPortList, 2);
	//#pragma region	whenMethodes
	//		When(Method(mockedAvrMicroRepository, analogReference)).AlwaysReturn();
	//		When(Method(mockedAvrMicroRepository, delay)).AlwaysReturn();
	//		When(Method(mockedAvrMicroRepository, digitalRead).Using(pin_pir_left)).AlwaysReturn(0);
	//		When(Method(mockedAvrMicroRepository, digitalRead).Using(pin_pir_right)).AlwaysReturn(0);
	//		When(Method(mockedAvrMicroRepository, analogRead).Using(pin_smoke_left)).AlwaysReturn(100);
	//		When(Method(mockedAvrMicroRepository, analogRead).Using(pin_smoke_right)).AlwaysReturn(1000);
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(const char*))).AlwaysDo([](const char* data) { (void)data;});
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(float))).AlwaysDo([](float data) { (void)data;});
	//		/*When(OverloadedMethod(mockedAvrMicroRepository, print, void(int, bool))).AlwaysDo([](int data, bool nl) { (void)data; (void)nl; });
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(uint8_t, bool))).AlwaysDo([](uint8_t data, bool nl) { (void)data; (void)nl; });*/
	//#pragma endregion
	//		Garage_Business_Layer garage_Business_Layer = Garage_Business_Layer();
	//		bool isDoorOpened = garage_Business_Layer.can_open_the_door(avrMicroRepository, pirActivity, smokeActivity);
	//		Assert::IsTrue(isDoorOpened, L"Expected the door to be opened when both smoke sensors are inactive (0).");
	//	}
	//	TEST_METHOD(Test_open_garage_door_human_no_smoke_no) {
	//		Mock<AvrMicroRepository> mockedAvrMicroRepository;
	//		AvrMicroRepository& avrMicroRepository = mockedAvrMicroRepository.get();
	//		DigitalPort pir_sensor_left = DigitalPort("Pi0", pin_pir_left, DigitalPort::AlarmTriggerOn::high, DigitalPort::PortDirection::input);
	//		DigitalPort pir_sensor_right = DigitalPort("Pi1", pin_pir_right, DigitalPort::AlarmTriggerOn::high, DigitalPort::PortDirection::input);
	//		DigitalPort* digitalPortList[] = { &pir_sensor_left ,&pir_sensor_right };
	//		AnalogPort smoke_sensor_left = AnalogPort("Sm1", pin_smoke_left);
	//		AnalogPort smoke_sensor_right = AnalogPort("Sm2", pin_smoke_right);
	//		smoke_sensor_left.min_digital_alarm_value_in = 100;
	//		smoke_sensor_left.max_digital_alarm_value_in = 900;
	//		smoke_sensor_right.min_digital_alarm_value_in = 100;
	//		smoke_sensor_right.max_digital_alarm_value_in = 900;
	//		AnalogPort* analogPortList[] = { &smoke_sensor_left, &smoke_sensor_right };
	//		DigitalPortActivity pirActivity = DigitalPortActivity(digitalPortList, 2);
	//		AnalogPortActivity smokeActivity = AnalogPortActivity(analogPortList, 2);
	//#pragma region	whenMethodes
	//		When(Method(mockedAvrMicroRepository, analogReference)).AlwaysReturn();
	//		When(Method(mockedAvrMicroRepository, delay)).AlwaysReturn();
	//		When(Method(mockedAvrMicroRepository, digitalRead).Using(pin_pir_left)).AlwaysReturn(0);
	//		When(Method(mockedAvrMicroRepository, digitalRead).Using(pin_pir_right)).AlwaysReturn(0);
	//		When(Method(mockedAvrMicroRepository, analogRead).Using(pin_smoke_left)).AlwaysReturn(100);
	//		When(Method(mockedAvrMicroRepository, analogRead).Using(pin_smoke_right)).AlwaysReturn(500);
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(const char*))).AlwaysDo([](const char* data) { (void)data;});
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(float))).AlwaysDo([](float data) { (void)data;});
	//	/*	When(OverloadedMethod(mockedAvrMicroRepository, print, void(int, bool))).AlwaysDo([](int data, bool nl) { (void)data; (void)nl; });
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(uint8_t, bool))).AlwaysDo([](uint8_t data, bool nl) { (void)data; (void)nl; });*/
	//#pragma endregion
	//		Garage_Business_Layer garage_Business_Layer = Garage_Business_Layer();
	//		bool isDoorOpened = garage_Business_Layer.can_open_the_door(avrMicroRepository, pirActivity, smokeActivity);
	//		Assert::IsFalse(isDoorOpened, L"Expected the door to be opened when both smoke sensors are inactive (0).");
	//	}
	//	TEST_METHOD(Test_open_garage_door_human_yes_smoke_yes) {
	//		Mock<AvrMicroRepository> mockedAvrMicroRepository;
	//		AvrMicroRepository& avrMicroRepository = mockedAvrMicroRepository.get();
	//		DigitalPort pir_sensor_left = DigitalPort("Pi0", pin_pir_left, DigitalPort::AlarmTriggerOn::high, DigitalPort::PortDirection::input);
	//		DigitalPort pir_sensor_right = DigitalPort("Pi1", pin_pir_right, DigitalPort::AlarmTriggerOn::high, DigitalPort::PortDirection::input);
	//		DigitalPort* digitalPortList[] = { &pir_sensor_left ,&pir_sensor_right };
	//		AnalogPort smoke_sensor_left = AnalogPort("Sm1", pin_smoke_left);
	//		AnalogPort smoke_sensor_right = AnalogPort("Sm2", pin_smoke_right);
	//		smoke_sensor_left.min_digital_alarm_value_in = 100;
	//		smoke_sensor_left.max_digital_alarm_value_in = 900;
	//		smoke_sensor_right.min_digital_alarm_value_in = 100;
	//		smoke_sensor_right.max_digital_alarm_value_in = 900;
	//		AnalogPort* analogPortList[] = { &smoke_sensor_left, &smoke_sensor_right };
	//		DigitalPortActivity pirActivity = DigitalPortActivity(digitalPortList, 2);
	//		AnalogPortActivity smokeActivity = AnalogPortActivity(analogPortList, 2);
	//#pragma region	whenMethodes
	//		When(Method(mockedAvrMicroRepository, analogReference)).AlwaysReturn();
	//		When(Method(mockedAvrMicroRepository, delay)).AlwaysReturn();
	//		When(Method(mockedAvrMicroRepository, digitalRead).Using(pin_pir_left)).AlwaysReturn(0);
	//		When(Method(mockedAvrMicroRepository, digitalRead).Using(pin_pir_right)).AlwaysReturn(1);
	//		When(Method(mockedAvrMicroRepository, analogRead).Using(pin_smoke_left)).AlwaysReturn(100);
	//		When(Method(mockedAvrMicroRepository, analogRead).Using(pin_smoke_right)).AlwaysReturn(1000);
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(const char*))).AlwaysDo([](const char* data) { (void)data;});
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(float))).AlwaysDo([](float data) { (void)data;});
	//	/*	When(OverloadedMethod(mockedAvrMicroRepository, print, void(int, bool))).AlwaysDo([](int data, bool nl) { (void)data; (void)nl; });
	//		When(OverloadedMethod(mockedAvrMicroRepository, print, void(uint8_t, bool))).AlwaysDo([](uint8_t data, bool nl) { (void)data; (void)nl; });*/
	//#pragma endregion
	//		Garage_Business_Layer garage_Business_Layer = Garage_Business_Layer();
	//		bool isDoorOpened = garage_Business_Layer.can_open_the_door(avrMicroRepository, pirActivity, smokeActivity);
	//		Assert::IsFalse(isDoorOpened, L"Expected the door to be opened when both smoke sensors are inactive (0).");
	//	}
	//TEST_METHOD(Test_xxx) {
		//	Mock<BlueToothRepository> mockedBlueToothRepository;
		//	BlueToothRepository& avrMicroRepository = mockedBlueToothRepository.get();
		//	When(OverloadedMethod(mockedBlueToothRepository, is_device_detected, bool(char*, char*)))
		//		.AlwaysReturn(true);
		//	When(Method(mockedBlueToothRepository, set_to_slave_mode)).AlwaysReturn();
		//	When(Method(mockedBlueToothRepository, set_to_master_mode_v2)).AlwaysReturn();
		//	When(Method(mockedBlueToothRepository, isBluetoothOn)).AlwaysReturn(true);
		//	/*when(Method(mockedBlueToothRepository, set_to_master_mode_v3)).AlwaysReturn();
		//	when(Method(mockedBlueToothRepository, program_mode)).AlwaysReturn();
		//	when(Method(mockedBlueToothRepository, set_to_receve_mode)).AlwaysReturn();
		//	when(Method(mockedBlueToothRepository, turnOffBlueTooth)).AlwaysReturn();
		//	when(Method(mockedBlueToothRepository, turnOnBlueTooth)).AlwaysReturn();
		//	when(Method(mockedBlueToothRepository, isBluetoothOn)).AlwaysReturn(true);
		//	when(Method(mockedBlueToothRepository, get_version).Using("")).AlwaysReturn();*/
		//}
	};
}
