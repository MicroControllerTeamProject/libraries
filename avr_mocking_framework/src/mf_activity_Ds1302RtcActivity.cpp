// File: mf_activity_Ds1302RtcActivity.cpp
#include "mf_activity_Ds1302RtcActivity.h"

mf_activity_Ds1302RtcActivity::mf_activity_Ds1302RtcActivity(Ds1302RtcRepository& ds1302_rtc_repository)
    : ds1302_rtc_repository_(ds1302_rtc_repository) {
}

mf_activity_Ds1302RtcActivity::~mf_activity_Ds1302RtcActivity() {
}

bool mf_activity_Ds1302RtcActivity::try_get_date_time(Ds1302RtcDateTime& date_time) {
    if (!ds1302_rtc_repository_.is_ready()) {
        return false;
    }

    uint8_t burst_values[burst_registers_count] = {};
    if (!ds1302_rtc_repository_.read_clock_burst(burst_values, burst_registers_count)) {
        return false;
    }

    uint8_t seconds_value = burst_values[0];
    uint8_t minutes_value = burst_values[1];
    uint8_t hours_value = burst_values[2];
    uint8_t day_value = burst_values[3];
    uint8_t month_value = burst_values[4];
    uint8_t day_of_week_value = burst_values[5];
    uint8_t year_value = burst_values[6];

    uint8_t second = bcd_to_decimal(seconds_value & 0x7F);
    uint8_t minute = bcd_to_decimal(minutes_value & 0x7F);
    uint8_t day = bcd_to_decimal(day_value & 0x3F);
    uint8_t month = bcd_to_decimal(month_value & 0x1F);
    uint8_t day_of_week = bcd_to_decimal(day_of_week_value & 0x07);
    uint16_t year = 2000 + bcd_to_decimal(year_value);

    if (second > 59 || minute > 59 || month < 1 || month > 12 || day_of_week < 1 || day_of_week > 7) {
        return false;
    }

    if (!is_hour_register_valid(hours_value)) {
        return false;
    }

    uint8_t hour = 0;

    if ((hours_value & 0x80) != 0) {
        uint8_t hour_12 = bcd_to_decimal(hours_value & 0x1F);
        bool is_pm = (hours_value & 0x20) != 0;

        if (hour_12 == 12) {
            hour = is_pm ? 12 : 0;
        }
        else {
            hour = is_pm ? (uint8_t)(hour_12 + 12) : hour_12;
        }
    }
    else {
        hour = bcd_to_decimal(hours_value & 0x3F);
    }

    Ds1302RtcDateTime read_date_time = {};
    read_date_time.year = year;
    read_date_time.month = month;
    read_date_time.day = day;
    read_date_time.day_of_week = day_of_week;
    read_date_time.hour = hour;
    read_date_time.minute = minute;
    read_date_time.second = second;

    if (!is_date_time_valid(read_date_time)) {
        return false;
    }

    date_time = read_date_time;
    return true;
}

bool mf_activity_Ds1302RtcActivity::try_set_date_time(const Ds1302RtcDateTime& date_time) {
    if (!ds1302_rtc_repository_.is_ready()) {
        return false;
    }

    if (!is_date_time_valid(date_time)) {
        return false;
    }

    uint8_t burst_values[burst_registers_count] = {};
    burst_values[0] = decimal_to_bcd(date_time.second) & 0x7F;
    burst_values[1] = decimal_to_bcd(date_time.minute) & 0x7F;
    burst_values[2] = decimal_to_bcd(date_time.hour) & 0x3F;
    burst_values[3] = decimal_to_bcd(date_time.day) & 0x3F;
    burst_values[4] = decimal_to_bcd(date_time.month) & 0x1F;
    burst_values[5] = decimal_to_bcd(date_time.day_of_week) & 0x07;
    burst_values[6] = decimal_to_bcd((uint8_t)(date_time.year - 2000));
    burst_values[7] = 0x00;

    if (!ds1302_rtc_repository_.set_write_protection_enabled(false)) {
        return false;
    }

    if (!ds1302_rtc_repository_.write_clock_burst(burst_values, burst_registers_count)) {
        return false;
    }

    Ds1302RtcDateTime read_back_date_time = {};
    if (!try_get_date_time(read_back_date_time)) {
        return false;
    }

    return is_same_date_time(date_time, read_back_date_time);
}

bool mf_activity_Ds1302RtcActivity::is_date_time_valid(const Ds1302RtcDateTime& date_time) const {
    if (date_time.year < 2000 || date_time.year > 2099) {
        return false;
    }

    if (date_time.month < 1 || date_time.month > 12) {
        return false;
    }

    if (date_time.day_of_week < 1 || date_time.day_of_week > 7) {
        return false;
    }

    if (date_time.hour > 23 || date_time.minute > 59 || date_time.second > 59) {
        return false;
    }

    uint8_t days_in_month = get_days_in_month(date_time.year, date_time.month);
    if (days_in_month == 0 || date_time.day < 1 || date_time.day > days_in_month) {
        return false;
    }

    return true;
}

bool mf_activity_Ds1302RtcActivity::is_same_date_time(const Ds1302RtcDateTime& left, const Ds1302RtcDateTime& right) const {
    return left.year == right.year &&
        left.month == right.month &&
        left.day == right.day &&
        left.day_of_week == right.day_of_week &&
        left.hour == right.hour &&
        left.minute == right.minute &&
        left.second == right.second;
}

uint8_t mf_activity_Ds1302RtcActivity::decimal_to_bcd(uint8_t value) {
    return (uint8_t)(((value / 10) << 4) | (value % 10));
}

uint8_t mf_activity_Ds1302RtcActivity::bcd_to_decimal(uint8_t value) {
    return (uint8_t)(((value >> 4) * 10) + (value & 0x0F));
}

bool mf_activity_Ds1302RtcActivity::is_leap_year(uint16_t year) {
    return ((year % 4) == 0 && (year % 100) != 0) || ((year % 400) == 0);
}

uint8_t mf_activity_Ds1302RtcActivity::get_days_in_month(uint16_t year, uint8_t month) {
    static const uint8_t days_by_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month < 1 || month > 12) {
        return 0;
    }

    if (month == 2 && is_leap_year(year)) {
        return 29;
    }

    return days_by_month[month - 1];
}

bool mf_activity_Ds1302RtcActivity::is_hour_register_valid(uint8_t hour_register_value) {
    if ((hour_register_value & 0x80) != 0) {
        uint8_t hour_12 = bcd_to_decimal(hour_register_value & 0x1F);
        return hour_12 >= 1 && hour_12 <= 12;
    }

    uint8_t hour_24 = bcd_to_decimal(hour_register_value & 0x3F);
    return hour_24 <= 23;
}
