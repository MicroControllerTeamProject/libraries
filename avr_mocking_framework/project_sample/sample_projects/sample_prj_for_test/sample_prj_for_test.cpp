#include "pch.h"
#include "src/extend.h"
#include "CppUnitTest.h"
#include "../sample_prj_to_start/src/model/DeMuxPlexerStatus.h"
#include "../sample_prj_to_start/src/business/ControlUnit_BL.h"
#include <mf_repository_AvrMicroRepository.h>
#include <mf_commons_commonsLayer.h>
#include <mf_activity_AnalogPortDActivity.h>
#include <mf_activity_DigitalPortActivity.h>
#include <mf_activity_NTC3950thermistorActivity.h>
#include <mf_activity_AnalogPortCActivity.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace MockProjectSampleTest {
	TEST_CLASS(MockProjectSampleTest) {
		Mock<AvrMicroRepository> mockedAvrMicroRepository;
		AvrMicroRepository& avrMicroRepository = mockedAvrMicroRepository.get();
		long unsigned fake_get_mill = 0;
public:
	TEST_METHOD_INITIALIZE(Initialize) {
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
	TEST_METHOD(test_calculate_contribution_given_analog_port_offset) {
		When(Method(mockedAvrMicroRepository, pinMode)).AlwaysReturn();
		When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
		When(Method(mockedAvrMicroRepository, get_vref)).AlwaysReturn(4.70f);
		When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; });
		When(Method(mockedAvrMicroRepository, delay)).AlwaysReturn();
		AnalogPortC thermistor1('A', 0, 30.00f, 1.00f);
		AnalogPortC thermistor2('B', 0, 20.00f, 1.00f);
		DigitalPort relay_01('A', 11, mf::commons::commonsLayer::PortDirection::output);
		DigitalPort relay_02('B', 12, mf::commons::commonsLayer::PortDirection::output);
		AnalogPortC current1('A', 10, 20.00f, 2.00f, 0.50f, true);
		AnalogPortC current2('B', 13, 20.00f, 5.00f, 0.50f, true);
		AnalogPortC* current_list[2] = { &current1,&current2 };
		AnalogPortC* thermistor_list[2] = { &thermistor1 ,&thermistor2 };
		DigitalPort* relay_list[2] = { &relay_01,&relay_02 };
		AnalogPortCActivity currentActivity(avrMicroRepository, current_list, 2);
		DigitalPortActivity relayActivity(avrMicroRepository, relay_list, 2);
		NTC3950thermistorActivity ntc_3950thermistorActivity(avrMicroRepository, thermistor_list, 2, 100000.00f);
		std::vector<int> thermistor_values{512,512};
		std::vector<int> start_current_values{ 300,250 };
		size_t i = 0;
		ControlUnit_BL controlUnit_BL(avrMicroRepository, ntc_3950thermistorActivity, relayActivity, currentActivity);
		controlUnit_BL.turn_on_off_all_relays(true);
		When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return start_current_values[(i++) % start_current_values.size()]; });
		controlUnit_BL.calculate_current_sensors_offset(1);
		while (fake_get_mill < 10000) {
			i = 0;
			std::vector<int> runtime_current_values{ 350,300 };
			fake_get_mill += 1000;
			When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return thermistor_values[(i++) % thermistor_values.size()]; });
			controlUnit_BL.disable_relays_where_thermistor_is_on_alarm();
			When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return runtime_current_values[(i++) % runtime_current_values.size()]; });
			controlUnit_BL.disable_relays_where_current_is_on_alarm();
		}
		Assert::IsTrue(current1.digital_value == 50, L"Expected current1.digital_value = 50");
		Assert::IsTrue(current2.digital_value == 50, L"Expected current2.digital_value = 50");
	}
	TEST_METHOD(test_thermistor_sensors) {
		When(Method(mockedAvrMicroRepository, pinMode)).AlwaysReturn();
		When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
		When(Method(mockedAvrMicroRepository, get_vref)).AlwaysReturn(4.70f);
		When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; });
		When(Method(mockedAvrMicroRepository, delay)).AlwaysReturn();
		AnalogPortC thermistor1('A', 0, 30.00f, 1.00f);
		AnalogPortC thermistor2('B', 0, 20.00f, 1.00f);
		DigitalPort relay_01('A', 11, mf::commons::commonsLayer::PortDirection::output);
		DigitalPort relay_02('B', 12, mf::commons::commonsLayer::PortDirection::output);
		AnalogPortC current1('A', 10, 20.00f, 2.00f, 0.50f, true);
		AnalogPortC current2('B', 13, 20.00f, 5.00f, 0.50f, true);
		AnalogPortC* current_list[2] = { &current1,&current2 };
		AnalogPortC* thermistor_list[2] = { &thermistor1 ,&thermistor2 };
		DigitalPort* relay_list[2] = { &relay_01,&relay_02 };
		AnalogPortCActivity currentActivity(avrMicroRepository, current_list, 2);
		DigitalPortActivity relayActivity(avrMicroRepository, relay_list, 2);
		NTC3950thermistorActivity ntc_3950thermistorActivity(avrMicroRepository, thermistor_list, 2, 100000.00f);
		//Ntc on 512 digital value = 25.00°C, on 400 digital value = 30.00°C, on 300 digital value = 35.00°C
		std::vector<int> thermistor_values{ 400,512 };
		std::vector<int> start_current_values{ 300,250 };
		size_t i = 0;
		ControlUnit_BL controlUnit_BL(avrMicroRepository, ntc_3950thermistorActivity, relayActivity, currentActivity);
		controlUnit_BL.turn_on_off_all_relays(true);
		When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return start_current_values[(i++) % start_current_values.size()]; });
		controlUnit_BL.calculate_current_sensors_offset(1);
		while (fake_get_mill < 10000) {
			i = 0;
			std::vector<int> runtime_current_values{ 350,300 };
			fake_get_mill += 1000;
			When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return thermistor_values[(i++) % thermistor_values.size()]; });
			controlUnit_BL.disable_relays_where_thermistor_is_on_alarm();
			When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return runtime_current_values[(i++) % runtime_current_values.size()]; });
			controlUnit_BL.disable_relays_where_current_is_on_alarm();
		}
		Assert::IsTrue(relay_01.pin_value_for_tdd, L"Expected relay_01 to be enabled");
		Assert::IsFalse(relay_02.pin_value_for_tdd, L"Expected relay_02 to be disabled");
	}
	TEST_METHOD(test_thermistor_sensors_time_elapsed) {
		When(Method(mockedAvrMicroRepository, pinMode)).AlwaysReturn();
		When(Method(mockedAvrMicroRepository, digitalWrite)).AlwaysReturn();
		When(Method(mockedAvrMicroRepository, get_vref)).AlwaysReturn(4.70f);
		When(Method(mockedAvrMicroRepository, get_millis)).AlwaysDo([&] { return fake_get_mill; });
		When(Method(mockedAvrMicroRepository, delay)).AlwaysReturn();
		AnalogPortC thermistor1('A', 0, 30.00f, 1.00f);
		AnalogPortC thermistor2('B', 0, 20.00f, 1.00f);
		DigitalPort relay_01('A', 11, mf::commons::commonsLayer::PortDirection::output);
		DigitalPort relay_02('B', 12, mf::commons::commonsLayer::PortDirection::output);
		AnalogPortC current1('A', 10, 20.00f, 2.00f, 0.50f, true);
		AnalogPortC current2('B', 13, 20.00f, 5.00f, 0.50f, true);
		AnalogPortC* current_list[2] = { &current1,&current2 };
		AnalogPortC* thermistor_list[2] = { &thermistor1 ,&thermistor2 };
		DigitalPort* relay_list[2] = { &relay_01,&relay_02 };
		AnalogPortCActivity currentActivity(avrMicroRepository, current_list, 2);
		DigitalPortActivity relayActivity(avrMicroRepository, relay_list, 2);
		NTC3950thermistorActivity ntc_3950thermistorActivity(avrMicroRepository, thermistor_list, 2, 100000.00f);
		//Ntc on 512 digital value = 25.00°C, on 400 digital value = 30.00°C, on 300 digital value = 35.00°C
		std::vector<int> thermistor_values{ 400,512 };
		std::vector<int> start_current_values{ 300,250 };
		size_t i = 0;
		ControlUnit_BL controlUnit_BL(avrMicroRepository, ntc_3950thermistorActivity, relayActivity, currentActivity);
		controlUnit_BL.turn_on_off_all_relays(true);
		When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return start_current_values[(i++) % start_current_values.size()]; });
		controlUnit_BL.calculate_current_sensors_offset(1);
		//set alarm time to 15 seconds for test
		thermistor2.set_alarm_if_above_threshold_for_seconds = 15;
		while (fake_get_mill < 5000) {
			i = 0;
			std::vector<int> runtime_current_values{ 350,300 };
			fake_get_mill += 1000;
			When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return thermistor_values[(i++) % thermistor_values.size()]; });
			controlUnit_BL.disable_relays_where_thermistor_is_on_alarm();
			When(Method(mockedAvrMicroRepository, analogRead).Using(21)).AlwaysDo([&](int) { return runtime_current_values[(i++) % runtime_current_values.size()]; });
			controlUnit_BL.disable_relays_where_current_is_on_alarm();
		}
		Assert::IsTrue(relay_01.pin_value_for_tdd, L"Expected relay_01 to be enabled");
		Assert::IsTrue(relay_02.pin_value_for_tdd, L"Expected relay_02 to be enabled for time elapsed");
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
