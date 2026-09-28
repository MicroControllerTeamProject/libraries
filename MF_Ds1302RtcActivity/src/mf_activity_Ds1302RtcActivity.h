// File: mf_activity_Ds1302RtcActivity.h
#pragma once

#include <stdint.h>

#include "mf_repository_Ds1302RtcRepository.h"

class mf_activity_Ds1302RtcActivity {
public:
    explicit mf_activity_Ds1302RtcActivity(Ds1302RtcRepository& ds1302_rtc_repository);
    virtual ~mf_activity_Ds1302RtcActivity();

    virtual bool try_get_date_time(Ds1302RtcDateTime& date_time);
    virtual bool try_set_date_time(const Ds1302RtcDateTime& date_time);
    virtual bool is_date_time_valid(const Ds1302RtcDateTime& date_time) const;
    virtual bool is_same_date_time(const Ds1302RtcDateTime& left, const Ds1302RtcDateTime& right) const;

private:
    static const uint8_t burst_registers_count = 8;

    Ds1302RtcRepository& ds1302_rtc_repository_;

    static uint8_t decimal_to_bcd(uint8_t value);
    static uint8_t bcd_to_decimal(uint8_t value);
    static bool is_leap_year(uint16_t year);
    static uint8_t get_days_in_month(uint16_t year, uint8_t month);
    static bool is_hour_register_valid(uint8_t hour_register_value);
};
