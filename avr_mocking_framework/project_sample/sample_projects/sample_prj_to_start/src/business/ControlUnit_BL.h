#pragma once
#include <mf_activity_DigitalPortActivity.h>
#include <mf_activity_AnalogPortCActivity.h>
#include <mf_activity_NTC3950thermistorActivity.h>
#include "../../AppConfig.h"
#include <stdint.h>
#if _ON_MOCKING_TESTS
#include "../model/DeMuxPlexerEntity.h"
#endif // _on_mocking_tests
class ControlUnit_BL {
public:
	ControlUnit_BL(AvrMicroRepository& avrMicroRepository, NTC3950thermistorActivity& thermistorActivity,DigitalPortActivity& relayActivity, AnalogPortCActivity& currentActivity);
	~ControlUnit_BL();
#if _ON_MOCKING_TESTS
	DeMuxPlexerEntity demux_plexer_entity; // Entità del demultiplexer (solo per test)
#endif // _on_mocking_tests
	bool disable_relays_where_thermistor_is_on_alarm();
	bool disable_relays_where_current_is_on_alarm();
	void turn_on_off_all_relays(bool turn_on);
	void calculate_current_sensors_offset(uint8_t number_of_read);
private:
	void reset_counter();
	void set_position_counter(uint8_t position);
	void enable_demux_sensors();
	void disable_demux_sensors();
	bool is_thermistor_port_values_out_of_range();
	bool is_current_port_values_out_of_range();
	bool turn_off_relay_by_group(char group_id);
	AvrMicroRepository& avrMicroRepository; // Riferimento al repository AVR
	NTC3950thermistorActivity& thermistorActivity;
	DigitalPortActivity& relayActivity;
	AnalogPortCActivity& currentActivity;
};
