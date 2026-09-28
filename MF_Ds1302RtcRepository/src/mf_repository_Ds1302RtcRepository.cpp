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

    uint8_t seconds_value = 0;
    if (!read_register(seconds_register_read, seconds_value)) {
        return false;
    }

    uint8_t seconds = bcd_to_decimal(seconds_value & 0x7F);
    if (seconds > 59) {
        return false;
    }

    return (seconds_value & clock_halt_mask) == 0;
}

bool Ds1302RtcRepository::set_write_protection_enabled(bool is_enabled) {
    if (!is_ready_) {
        return false;
    }

    if (!write_register(control_register_write, is_enabled ? write_protection_mask : 0x00)) {
        return false;
    }

    uint8_t control_value = 0;
    if (!read_register(control_register_read, control_value)) {
        return false;
    }

    bool is_write_protection_enabled = (control_value & write_protection_mask) != 0;
    return is_write_protection_enabled == is_enabled;
}

bool Ds1302RtcRepository::write_register(uint8_t command, uint8_t value) {
    if (!is_ready_) {
        return false;
    }

    start_transaction();
    write_byte(command);
    write_byte(value);
    end_transaction();
    return true;
}

bool Ds1302RtcRepository::read_register(uint8_t command, uint8_t& value) {
    if (!is_ready_) {
        return false;
    }

    start_transaction();
    write_byte(command);
    value = read_byte();
    end_transaction();
    return true;
}

bool Ds1302RtcRepository::write_clock_burst(const uint8_t* values, uint8_t values_count) {
    if (!is_ready_ || values == 0 || values_count != burst_registers_count) {
        return false;
    }

    start_transaction();
    write_byte(clock_burst_write);

    for (uint8_t index = 0; index < burst_registers_count; index++) {
        write_byte(values[index]);
    }

    end_transaction();
    return true;
}

bool Ds1302RtcRepository::read_clock_burst(uint8_t* values, uint8_t values_count) {
    if (!is_ready_ || values == 0 || values_count != burst_registers_count) {
        return false;
    }

    start_transaction();
    write_byte(clock_burst_read);

    for (uint8_t index = 0; index < burst_registers_count; index++) {
        values[index] = read_byte();
    }

    end_transaction();
    return true;
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

uint8_t Ds1302RtcRepository::decimal_to_bcd(uint8_t value) {
    return (uint8_t)(((value / 10) << 4) | (value % 10));
}

uint8_t Ds1302RtcRepository::bcd_to_decimal(uint8_t value) {
    return (uint8_t)(((value >> 4) * 10) + (value & 0x0F));
}
