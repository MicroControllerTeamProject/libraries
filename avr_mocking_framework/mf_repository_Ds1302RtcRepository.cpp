// File: mf_repository_Ds1302RtcRepository.cpp
#include "mf_repository_Ds1302RtcRepository.h"

#include <Arduino.h>

Ds1302RtcRepository::Ds1302RtcRepository() {
}

Ds1302RtcRepository::~Ds1302RtcRepository() {
}

bool Ds1302RtcRepository::begin(uint8_t clock_pin, uint8_t data_pin, uint8_t reset_pin) {
    if (clock_pin == data_pin || clock_pin == reset_pin || data_pin == reset_pin) {
        is_ready_ = false;
        return false;
    }

    clock_pin_ = clock_pin;
    data_pin_ = data_pin;
    reset_pin_ = reset_pin;

    pinMode(clock_pin_, OUTPUT);
    pinMode(reset_pin_, OUTPUT);
    pinMode(data_pin_, INPUT);

    digitalWrite(clock_pin_, LOW);
    digitalWrite(reset_pin_, LOW);

    is_ready_ = true;
    return true;
}

void Ds1302RtcRepository::close() {
    if (!is_ready_) {
        return;
    }

    digitalWrite(reset_pin_, LOW);
    digitalWrite(clock_pin_, LOW);
    pinMode(data_pin_, INPUT);

    is_ready_ = false;
}

bool Ds1302RtcRepository::is_ready() const {
    return is_ready_;
}

bool Ds1302RtcRepository::is_clock_running() {
    if (!is_ready_) {
        return false;
    }

    uint8_t seconds_value = read_register(seconds_register_read);
    uint8_t seconds_bcd = seconds_value & 0x7F;
    uint8_t seconds = bcd_to_decimal(seconds_bcd);

    if (seconds > 59) {
        return false;
    }

    return (seconds_value & clock_halt_mask) == 0;
}

bool Ds1302RtcRepository::try_get_date_time(Ds1302RtcDateTime& date_time) {
    if (!is_ready_) {
        return false;
    }

    uint8_t burst_values[burst_registers_count] = {};
    read_clock_burst(burst_values);

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

    uint8_t hour = 0;
    if (!is_hour_register_valid(hours_value)) {
        return false;
    }

    if ((hours_value & 0x80) != 0) {
        uint8_t hour_12 = bcd_to_decimal(hours_value & 0x1F);
        bool is_pm = (hours_value & 0x20) != 0;

        if (hour_12 < 1 || hour_12 > 12) {
            return false;
        }

        if (hour_12 == 12) {
            hour = is_pm ? 12 : 0;
        }
        else {
            hour = is_pm ? (hour_12 + 12) : hour_12;
        }
    }
    else {
        hour = bcd_to_decimal(hours_value & 0x3F);
    }

    if (second > 59 || minute > 59 || month < 1 || month > 12 || day_of_week < 1 || day_of_week > 7) {
        return false;
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

bool Ds1302RtcRepository::try_set_date_time(const Ds1302RtcDateTime& date_time) {
    if (!is_ready_ || !is_date_time_valid(date_time)) {
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

    write_register(control_register_write, 0x00);
    write_clock_burst(burst_values);

    Ds1302RtcDateTime read_back_date_time = {};
    if (!try_get_date_time(read_back_date_time)) {
        return false;
    }

    return is_same_date_time(date_time, read_back_date_time);
}

bool Ds1302RtcRepository::set_write_protection_enabled(bool is_enabled) {
    if (!is_ready_) {
        return false;
    }

    write_register(control_register_write, is_enabled ? write_protection_mask : 0x00);

    uint8_t control_value = read_register(control_register_read);
    bool is_write_protection_enabled = (control_value & write_protection_mask) != 0;
    return is_write_protection_enabled == is_enabled;
}

void Ds1302RtcRepository::start_transaction() {
    digitalWrite(reset_pin_, LOW);
    digitalWrite(clock_pin_, LOW);
    delayMicroseconds(4);
    digitalWrite(reset_pin_, HIGH);
    delayMicroseconds(4);
}

void Ds1302RtcRepository::end_transaction() {
    digitalWrite(reset_pin_, LOW);
    delayMicroseconds(4);
    pinMode(data_pin_, INPUT);
}

void Ds1302RtcRepository::write_byte(uint8_t value) {
    pinMode(data_pin_, OUTPUT);

    for (uint8_t bit_index = 0; bit_index < 8; bit_index++) {
        digitalWrite(data_pin_, ((value >> bit_index) & 0x01) != 0 ? HIGH : LOW);
        delayMicroseconds(1);
        digitalWrite(clock_pin_, HIGH);
        delayMicroseconds(1);
        digitalWrite(clock_pin_, LOW);
    }
}

uint8_t Ds1302RtcRepository::read_byte() {
    uint8_t value = 0;
    pinMode(data_pin_, INPUT);
    delayMicroseconds(1);

    for (uint8_t bit_index = 0; bit_index < 8; bit_index++) {
        if (digitalRead(data_pin_) != LOW) {
            value |= (1 << bit_index);
        }

        digitalWrite(clock_pin_, HIGH);
        delayMicroseconds(1);
        digitalWrite(clock_pin_, LOW);
        delayMicroseconds(1);
    }

    return value;
}

void Ds1302RtcRepository::write_register(uint8_t command, uint8_t value) {
    start_transaction();
    write_byte(command);
    write_byte(value);
    end_transaction();
}

uint8_t Ds1302RtcRepository::read_register(uint8_t command) {
    start_transaction();
    write_byte(command);
    uint8_t value = read_byte();
    end_transaction();
    return value;
}

void Ds1302RtcRepository::write_clock_burst(const uint8_t* values) {
    start_transaction();
    write_byte(clock_burst_write);

    for (uint8_t index = 0; index < burst_registers_count; index++) {
        write_byte(values[index]);
    }

    end_transaction();
}

void Ds1302RtcRepository::read_clock_burst(uint8_t* values) {
    start_transaction();
    write_byte(clock_burst_read);

    for (uint8_t index = 0; index < burst_registers_count; index++) {
        values[index] = read_byte();
    }

    end_transaction();
}

uint8_t Ds1302RtcRepository::decimal_to_bcd(uint8_t value) {
    return (uint8_t)(((value / 10) << 4) | (value % 10));
}

uint8_t Ds1302RtcRepository::bcd_to_decimal(uint8_t value) {
    return (uint8_t)(((value >> 4) * 10) + (value & 0x0F));
}

bool Ds1302RtcRepository::is_leap_year(uint16_t year) {
    return ((year % 4) == 0 && (year % 100) != 0) || ((year % 400) == 0);
}

uint8_t Ds1302RtcRepository::get_days_in_month(uint16_t year, uint8_t month) {
    static const uint8_t days_by_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month < 1 || month > 12) {
        return 0;
    }

    if (month == 2 && is_leap_year(year)) {
        return 29;
    }

    return days_by_month[month - 1];
}

bool Ds1302RtcRepository::is_date_time_valid(const Ds1302RtcDateTime& date_time) {
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

bool Ds1302RtcRepository::is_same_date_time(const Ds1302RtcDateTime& left, const Ds1302RtcDateTime& right) {
    return left.year == right.year &&
        left.month == right.month &&
        left.day == right.day &&
        left.day_of_week == right.day_of_week &&
        left.hour == right.hour &&
        left.minute == right.minute &&
        left.second == right.second;
}

bool Ds1302RtcRepository::is_hour_register_valid(uint8_t hour_register_value) {
    if ((hour_register_value & 0x80) != 0) {
        uint8_t hour_12 = bcd_to_decimal(hour_register_value & 0x1F);
        return hour_12 >= 1 && hour_12 <= 12;
    }

    uint8_t hour_24 = bcd_to_decimal(hour_register_value & 0x3F);
    return hour_24 <= 23;
}
