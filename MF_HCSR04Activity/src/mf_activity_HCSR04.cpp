// mf_activity_HCSR04.cpp
#include <mf_activity_HCSR04.h>

HCSR04Activity::HCSR04Activity(HC_SR04_Repository& hc_sr04_Repository,
    AvrMicroRepository& avrMicroRepository,
    uint16_t min_dist_alarm_cm,
    uint16_t max_dist_alarm_cm,
    unsigned long out_of_range_hold_ms)
    : hc_sr04_Repository(hc_sr04_Repository),
    avrMicroRepository(avrMicroRepository),
    min_dist_alarm_cm(min_dist_alarm_cm),
    max_dist_alarm_cm(max_dist_alarm_cm),
    out_of_range_hold_ms(out_of_range_hold_ms)
{
}

int16_t HCSR04Activity::read_distance_cm_avg(unsigned long timeout_us,
    uint8_t samples,
    uint8_t inter_delay_ms,
    bool trim_min_max)
{
    if (samples == 0) return -1;

    int32_t sum = 0;
    uint8_t valid = 0;

    int16_t min_v = 32767;
    int16_t max_v = -32768;

    for (uint8_t i = 0; i < samples; ++i) {
        int16_t d = hc_sr04_Repository.measure_distance_cm(timeout_us);
        if (d >= 0) {
            sum += d;
            valid++;
            if (d < min_v) min_v = d;
            if (d > max_v) max_v = d;
        }
        if (inter_delay_ms) this->avrMicroRepository.delay(inter_delay_ms);
    }

    if (valid == 0) return -1;

    if (trim_min_max && valid >= 3) {
        sum -= (int32_t)min_v;
        sum -= (int32_t)max_v;
        valid -= 2;
    }

    return (int16_t)((sum + (valid / 2)) / valid);
}

int8_t HCSR04Activity::get_range_state(unsigned long timeout_us,
    uint8_t samples,
    uint8_t inter_delay_ms,
    bool trim_min_max)
{
    int16_t distance_cm = read_distance_cm_avg(timeout_us, samples, inter_delay_ms, trim_min_max);

    if (distance_cm < 0) return -1;

    bool out_now = (distance_cm < (int16_t)min_dist_alarm_cm) ||
        (distance_cm > (int16_t)max_dist_alarm_cm);

    return out_now ? 1 : 0;
}

bool HCSR04Activity::is_distance_out_of_range_now(unsigned long timeout_us,
    uint8_t samples,
    uint8_t inter_delay_ms,
    bool trim_min_max)
{
    int8_t st = get_range_state(timeout_us, samples, inter_delay_ms, trim_min_max);

    if (st < 0) {
        // invalida: reset entrambi
        out_pending = false; out_start_ms = 0;
        in_pending = false; in_start_ms = 0;
        return false;
    }

    if (st == 1) {
        // OUT adesso -> reset timer IN
        in_pending = false; in_start_ms = 0;
        return true;
    }

    // IN adesso -> reset timer OUT
    out_pending = false; out_start_ms = 0;
    return false;
}

bool HCSR04Activity::is_distance_out_of_range_for_ms(unsigned long timeout_us,
    uint8_t samples,
    uint8_t inter_delay_ms,
    bool trim_min_max)
{
    if (!is_distance_out_of_range_now(timeout_us, samples, inter_delay_ms, trim_min_max)) {
        return false;
    }

    if (out_of_range_hold_ms == 0) return true;

    unsigned long now_ms = this->avrMicroRepository.get_millis();

    if (!out_pending) {
        out_pending = true;
        out_start_ms = now_ms;
        return false;
    }

    return ((unsigned long)(now_ms - out_start_ms) >= out_of_range_hold_ms);
}

bool HCSR04Activity::is_distance_in_range_now(unsigned long timeout_us,
    uint8_t samples,
    uint8_t inter_delay_ms,
    bool trim_min_max)
{
    int8_t st = get_range_state(timeout_us, samples, inter_delay_ms, trim_min_max);

    if (st < 0) {
        // invalida: reset entrambi
        out_pending = false; out_start_ms = 0;
        in_pending = false; in_start_ms = 0;
        return false; // invalida != in-range
    }

    if (st == 0) {
        // IN adesso -> reset timer OUT
        out_pending = false; out_start_ms = 0;
        return true;
    }

    // OUT adesso -> reset timer IN
    in_pending = false; in_start_ms = 0;
    return false;
}

bool HCSR04Activity::is_distance_in_range_for_ms(unsigned long timeout_us,
    uint8_t samples,
    uint8_t inter_delay_ms,
    bool trim_min_max)
{
    if (!is_distance_in_range_now(timeout_us, samples, inter_delay_ms, trim_min_max)) {
        return false;
    }

    if (out_of_range_hold_ms == 0) return true;

    unsigned long now_ms = this->avrMicroRepository.get_millis();

    if (!in_pending) {
        in_pending = true;
        in_start_ms = now_ms;
        return false;
    }

    return ((unsigned long)(now_ms - in_start_ms) >= out_of_range_hold_ms);
}
