#include "GarageGateController_BL.h"
GarageGateController_BL::GarageGateController_BL(AvrMicroRepository& avrMicroRepository,
	NTC3950thermistorActivity ntc3950thermistorActivity,
	HCSR04Activity hcsR04Activity, DigitalPortActivity gate_rele_activity)
	:avrMicroRepository(avrMicroRepository),
	ntc3950thermistorActivity(ntc3950thermistorActivity),
	hcsR04Activity(hcsR04Activity),
	gate_rele_activity(gate_rele_activity) {
}
bool GarageGateController_BL::open_the_door() {
	if (!ntc3950thermistorActivity.is_any_port_out_of_range() && hcsR04Activity.is_distance_in_range_for_ms()) {
		gate_rele_activity.digital_write(gate_rele_activity.get_digital_ports()[0]->get_pin(), true);
		return true;
	}
	return false;
}
