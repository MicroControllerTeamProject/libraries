// mf_activity_HCSR04.h
#pragma once
#include <stdint.h>
#include "mf_repository_HCSR04Repository.h"
#include "mf_repository_AvrMicroRepository.h"
#include "mf_activity_DigitalPortActivity.h"

class HCSR04Activity {
public:
    HCSR04Activity(HC_SR04_Repository& hc_sr04_Repository,
        AvrMicroRepository& avrMicroRepository,
        uint16_t min_dist_alarm_cm,
        uint16_t max_dist_alarm_cm,
        unsigned long out_of_range_hold_ms);

    // OUT: istantaneo (media) -> TRUE se fuori range ORA
    bool is_distance_out_of_range_now(unsigned long timeout_us = 30000,
        uint8_t samples = 5,
        uint8_t inter_delay_ms = 60,
        bool trim_min_max = true);

    // OUT: TRUE solo se fuori range per almeno out_of_range_hold_ms (continuo)
    bool is_distance_out_of_range_for_ms(unsigned long timeout_us = 30000,
        uint8_t samples = 5,
        uint8_t inter_delay_ms = 60,
        bool trim_min_max = true);

    // IN: istantaneo (media) -> TRUE se dentro range ORA
    bool is_distance_in_range_now(unsigned long timeout_us = 30000,
        uint8_t samples = 5,
        uint8_t inter_delay_ms = 60,
        bool trim_min_max = true);

    // IN: TRUE solo se dentro range per almeno out_of_range_hold_ms (continuo)
    // (uso lo stesso hold per risparmiare membri/config)
    bool is_distance_in_range_for_ms(unsigned long timeout_us = 30000,
        uint8_t samples = 5,
        uint8_t inter_delay_ms = 60,
        bool trim_min_max = true);

private:
    HC_SR04_Repository& hc_sr04_Repository;
    AvrMicroRepository& avrMicroRepository;
    uint16_t min_dist_alarm_cm;
    uint16_t max_dist_alarm_cm;
    unsigned long out_of_range_hold_ms;
    // debounce temporale OUT
    bool out_pending = false;
    unsigned long out_start_ms = 0;
    // debounce temporale IN
    bool in_pending = false;
    unsigned long in_start_ms = 0;
    int16_t read_distance_cm_avg(unsigned long timeout_us,
        uint8_t samples,
        uint8_t inter_delay_ms,
        bool trim_min_max);

    // -1: invalida/timeout, 0: IN range, 1: OUT of range
    int8_t get_range_state(unsigned long timeout_us,
        uint8_t samples,
        uint8_t inter_delay_ms,
        bool trim_min_max);
};
