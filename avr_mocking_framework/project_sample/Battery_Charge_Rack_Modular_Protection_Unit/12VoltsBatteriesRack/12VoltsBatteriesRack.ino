/*
 Name:		GarageApplication.ino
 Created:	6/6/2025 10:43:44 AM
 Author:	luigi.santagada
*/
#include <Arduino.h>
#include "src/model/AppConfig.h"
#include <mf_model_DigitalPort.h>
#include <SoftwareSerial.h>
#include <mf_adapter_SoftwareSerialAdapter.h>
#include <mf_activity_DigitalPortActivity.h>
#include <mf_activity_AnalogPortCActivity.h>
#include "src/business/ControlUnit_BL.h"
SoftwareSerial softSerial(99, 99);					 // RX, TX (esempio, usa i pin 10 e 11 per SoftwareSerial)
SoftwareSerialAdapter softSerialAdapter(softSerial); // Istanza SoftwareSerialAdapter
AvrMicroRepository avrMicroRepository_SSerial = AvrMicroRepository(softSerialAdapter, mf::commons::commonsLayer::AnalogRefMode::DEFAULT_m, 5.0f);
// RELAYS HAVE REAL MICROCONTROLLER PINS.
DigitalPort relay_01('A', 11, mf::commons::commonsLayer::PortDirection::output);
DigitalPort relay_02('B', 10, mf::commons::commonsLayer::PortDirection::output);
DigitalPort relay_03('C', 9, mf::commons::commonsLayer::PortDirection::output);
DigitalPort relay_04('D', 8, mf::commons::commonsLayer::PortDirection::output);
DigitalPort relay_05('E', A0, mf::commons::commonsLayer::PortDirection::output);
DigitalPort relay_06('F', A1, mf::commons::commonsLayer::PortDirection::output);

// THERMISTORS USE ANALOG MULTIPLEXER PINS, NOT REAL MICROCONTROLLER PINS.
AnalogPortC thermistor1('A', 0, 40.00f, 1.00f);
AnalogPortC thermistor2('B', 1, 40.00f, 1.00f);
AnalogPortC thermistor3('C', 2, 60.00f, 1.00f);
AnalogPortC thermistor4('D', 3, 60.00f, 1.00f);
AnalogPortC thermistor5('E', 4, 60.00f, 1.00f);
AnalogPortC thermistor6('F', 5, 60.00f, 1.00f);

// CURRENTS USE ANALOG MULTIPLEXER PINS, NOT REAL MICROCONTROLLER PINS.
AnalogPortC current1('A', 10, 20.00f, 5.00f, 0.40f, true);
AnalogPortC current2('B', 11, 20.00f, 5.00f, 0.40f, true);
AnalogPortC current3('C', 12, 20.00f, 5.00f, 0.40f, true);
AnalogPortC current4('D', 13, 20.00f, 5.00f, 0.40f, true);
AnalogPortC current5('E', 14, 20.00f, 5.00f, 0.40f, true);
AnalogPortC current6('F', 15, 20.00f, 5.00f, 0.40f, true);
AnalogPortC *current_list[6] = {&current1, &current2, &current3, &current4, &current5, &current6};
AnalogPortC *thermistor_list[6] = {&thermistor1, &thermistor2, &thermistor3, &thermistor4, &thermistor5, &thermistor6};
DigitalPort *relay_list[6] = {&relay_01, &relay_02, &relay_03, &relay_04, &relay_05, &relay_06};
AnalogPortCActivity currentActivity(avrMicroRepository_SSerial, current_list, 6);
DigitalPortActivity relayActivity(avrMicroRepository_SSerial, relay_list, 6);
// NTC3950 thermistor activity : USED ONLY 4 THERMISTORS FOR CABLE LIMITATIONS
NTC3950thermistorActivity ntc_3950thermistorActivity(avrMicroRepository_SSerial, thermistor_list, 4, 100000.00f);
AppConfig appConfig;
ControlUnit_BL controlUnit_BL(avrMicroRepository_SSerial, appConfig, ntc_3950thermistorActivity, relayActivity, currentActivity);
void setup(){
	Serial.begin(9600);
	pinMode(A7, INPUT);
	set_alarm_times_for_thermistor_sensors();
	set_alarm_times_for_current_sensors();
	bool any_port_is_on_alarm = false;
	controlUnit_BL.turn_on_off_all_relays(false);
	delay(2000);
	controlUnit_BL.calculate_current_sensors_offset(50);
	controlUnit_BL.turn_on_off_all_relays(true);
}
void loop(){
	// controlUnit_BL.disable_relays_where_thermistor_is_on_alarm();
	controlUnit_BL.disable_relays_where_current_is_on_alarm();
}
void set_alarm_times_for_thermistor_sensors(){
	thermistor1.set_alarm_if_above_threshold_for_seconds = 5;
	thermistor2.set_alarm_if_above_threshold_for_seconds = 5;
	thermistor3.set_alarm_if_above_threshold_for_seconds = 5;
	thermistor4.set_alarm_if_above_threshold_for_seconds = 5;
	thermistor5.set_alarm_if_above_threshold_for_seconds = 5;
	thermistor6.set_alarm_if_above_threshold_for_seconds = 5;
}
void set_alarm_times_for_current_sensors(){
	// SET ALARMS TIMES FOR CURRENT SENSORS WHEN ABOVE THRESHOLDS
	current1.set_alarm_if_above_threshold_for_seconds = 5;
	current2.set_alarm_if_above_threshold_for_seconds = 5;
	current3.set_alarm_if_above_threshold_for_seconds = 5;
	current4.set_alarm_if_above_threshold_for_seconds = 5;
	current5.set_alarm_if_above_threshold_for_seconds = 5;
	current6.set_alarm_if_above_threshold_for_seconds = 5;

	// SET ALARMS TIMES FOR CURRENT SENSORS WHEN UNDER THRESHOLDS
	current1.set_alarm_if_under_threshold_for_seconds = 5;
	current2.set_alarm_if_under_threshold_for_seconds = 5;
	current3.set_alarm_if_under_threshold_for_seconds = 5;
	current4.set_alarm_if_under_threshold_for_seconds = 5;
	current5.set_alarm_if_under_threshold_for_seconds = 5;
	current6.set_alarm_if_under_threshold_for_seconds = 5;
}
