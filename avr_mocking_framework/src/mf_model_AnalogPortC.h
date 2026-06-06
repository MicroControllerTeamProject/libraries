// File: mf_model_AnalogPortC.h
#pragma once
#include <stdint.h>
#include <mf_model_AnalogPortB.h>

class AnalogPortC : public AnalogPortB {
public:
	AnalogPortC(char group_id, const uint8_t pin, float full_scale_unit_of_misure, float max_unit_of_misure_alarm_value, float min_unit_of_misure_alarm_value, bool unit_of_misure_is_centered = false, float unit_of_misure_sensitivity_volt = 0.0f);
	AnalogPortC(char group_id, const uint8_t pin, float max_unit_of_misure_alarm_value, float min_unit_of_misure_alarm_value);

	float getFullScaleUnitOfMisure() const;
	bool getIstUnitOfMisureCentered() const;
	float getMaxUnitOfMisureAlarmValue() const;
	float getMinUnitOfMisureAlarmValue() const;
	float getUnitOfMisureSensitivityVolt() const;

private:
	float full_scale_unit_of_misure = 0.00f;
	bool unit_of_misure_is_centered = false;
	float max_unit_of_misure_alarm_value = 0.00f;
	float min_unit_of_misure_alarm_value = 0.00f;
	float unit_of_misure_sensitivity_volt = 0.00f;
};