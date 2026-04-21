// File: mf_repository_Ds1302RtcRepository.h
#pragma once

#include <stdint.h>

struct Ds1302RtcDateTime {
    uint16_t year = 2000;
    uint8_t month = 1;
    uint8_t day = 1;
    uint8_t day_of_week = 1;
    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t second = 0;
};

class Ds1302RtcRepository {
public:
    Ds1302RtcRepository();
    virtual ~Ds1302RtcRepository();

    virtual bool begin(uint8_t clock_pin, uint8_t data_pin, uint8_t reset_pin);
    virtual void close();
    virtual bool is_ready() const;
    virtual bool is_clock_running();
    virtual bool try_get_date_time(Ds1302RtcDateTime& date_time);
    virtual bool try_set_date_time(const Ds1302RtcDateTime& date_time);
    virtual bool set_write_protection_enabled(bool is_enabled);

private:
    static const uint8_t seconds_register_read = 0x81;
    static const uint8_t seconds_register_write = 0x80;
    static const uint8_t control_register_read = 0x8F;
    static const uint8_t control_register_write = 0x8E;
    static const uint8_t clock_burst_read = 0xBF;
    static const uint8_t clock_burst_write = 0xBE;
    static const uint8_t clock_halt_mask = 0x80;
    static const uint8_t write_protection_mask = 0x80;
    static const uint8_t burst_registers_count = 8;

    uint8_t clock_pin_ = 0;
    uint8_t data_pin_ = 0;
    uint8_t reset_pin_ = 0;
    bool is_ready_ = false;

    void start_transaction();
    void end_transaction();
    void write_byte(uint8_t value);
    uint8_t read_byte();
    void write_register(uint8_t command, uint8_t value);
    uint8_t read_register(uint8_t command);
    void write_clock_burst(const uint8_t* values);
    void read_clock_burst(uint8_t* values);

    static uint8_t decimal_to_bcd(uint8_t value);
    static uint8_t bcd_to_decimal(uint8_t value);
    static bool is_leap_year(uint16_t year);
    static uint8_t get_days_in_month(uint16_t year, uint8_t month);
    static bool is_date_time_valid(const Ds1302RtcDateTime& date_time);
    static bool is_same_date_time(const Ds1302RtcDateTime& left, const Ds1302RtcDateTime& right);
    static bool is_hour_register_valid(uint8_t hour_register_value);
};
