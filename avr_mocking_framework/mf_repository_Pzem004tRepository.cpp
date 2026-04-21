// mf_repository_Pzem004tRepository.cpp
#include <mf_repository_Pzem004tRepository.h>
#include <Arduino.h>

namespace {
constexpr uint8_t pzem_default_address = 0xF8;
constexpr uint8_t pzem_min_address = 0x01;
constexpr uint8_t pzem_max_address = 0xF7;
constexpr unsigned long pzem_baud_rate = 9600UL;
constexpr unsigned long pzem_default_timeout_ms = 100UL;
constexpr unsigned long pzem_default_update_interval_ms = 200UL;
constexpr uint8_t pzem_read_holding_registers = 0x03;
constexpr uint8_t pzem_read_input_registers = 0x04;
constexpr uint8_t pzem_write_single_register = 0x06;
constexpr uint8_t pzem_reset_energy_command = 0x42;
constexpr uint16_t pzem_register_alarm_threshold = 0x0001;
constexpr uint16_t pzem_register_address = 0x0002;
constexpr uint16_t pzem_invalid_slave_address = 0xFFFF;
constexpr uint16_t pzem_max_power_alarm_watts = 25000;
constexpr uint8_t pzem_measures_response_length = 25;
constexpr uint8_t pzem_cmd_8_length = 8;
constexpr uint8_t pzem_reset_cmd_length = 4;
constexpr uint8_t pzem_read_address_response_length = 7;
}

Pzem004tRepository::Pzem004tRepository(ISerial& serial, uint8_t address)
    : serial_(serial),
      timeout_ms_(pzem_default_timeout_ms),
      update_interval_ms_(pzem_default_update_interval_ms),
      last_update_ms_(0UL),
      is_cache_valid_(false) {
    cached_measures_.current_x1000 = 0UL;
    cached_measures_.power_x10 = 0UL;
    cached_measures_.energy_wh = 0UL;
    cached_measures_.voltage_x10 = 0U;
    cached_measures_.frequency_x10 = 0U;
    cached_measures_.power_factor_x100 = 0U;
    cached_measures_.alarms = 0U;
    cached_measures_.address = (address >= pzem_min_address && address <= pzem_default_address) ? address : pzem_default_address;
    cached_measures_.is_connected = false;
    cached_measures_.is_data_valid = false;
}

void Pzem004tRepository::begin() {
    serial_.begin(pzem_baud_rate);
    serial_.setTimeout(timeout_ms_);
    clear_receive_buffer();
    invalidate_cache();
    last_update_ms_ = 0UL;
}

void Pzem004tRepository::set_timeout(unsigned long timeout_ms) {
    timeout_ms_ = timeout_ms;
    serial_.setTimeout(timeout_ms_);
}

unsigned long Pzem004tRepository::get_timeout() const {
    return timeout_ms_;
}

void Pzem004tRepository::set_update_interval(unsigned long update_interval_ms) {
    update_interval_ms_ = update_interval_ms;
}

unsigned long Pzem004tRepository::get_update_interval() const {
    return update_interval_ms_;
}

bool Pzem004tRepository::read_measures(Pzem004tMeasures& out_measures) {
    if (!update_cache()) {
        return false;
    }

    out_measures = cached_measures_;
    return true;
}

bool Pzem004tRepository::reset_energy() {
    uint8_t send_buffer[pzem_reset_cmd_length] = { cached_measures_.address, pzem_reset_energy_command, 0x00, 0x00 };

    set_crc(send_buffer, pzem_reset_cmd_length);
    clear_receive_buffer();
    serial_.write(send_buffer, pzem_reset_cmd_length);
    invalidate_cache();

    return true;
}

bool Pzem004tRepository::set_power_alarm(uint16_t watts) {
    if (watts > pzem_max_power_alarm_watts) {
        watts = pzem_max_power_alarm_watts;
    }

    return send_cmd_8(pzem_write_single_register, pzem_register_alarm_threshold, watts, true);
}

bool Pzem004tRepository::set_address(uint8_t address) {
    if (address < pzem_min_address || address > pzem_max_address) {
        return false;
    }

    if (!send_cmd_8(pzem_write_single_register, pzem_register_address, address, true)) {
        return false;
    }

    cached_measures_.address = address;
    invalidate_cache();
    return true;
}

uint8_t Pzem004tRepository::read_address(bool update_internal_address) {
    uint8_t response[pzem_read_address_response_length];

    if (!send_cmd_8(pzem_read_holding_registers, pzem_register_address, 0x0001, false)) {
        return 0x00;
    }

    if (receive_frame(response, pzem_read_address_response_length) != pzem_read_address_response_length) {
        return 0x00;
    }

    uint8_t address = static_cast<uint8_t>((static_cast<uint16_t>(response[3]) << 8) | response[4]);
    if (update_internal_address) {
        cached_measures_.address = address;
        invalidate_cache();
    }

    return address;
}

uint8_t Pzem004tRepository::get_address() const {
    return cached_measures_.address;
}

bool Pzem004tRepository::is_connected() const {
    return cached_measures_.is_connected;
}

bool Pzem004tRepository::update_cache() {
    unsigned long now = get_millis();
    if (is_cache_valid_ && static_cast<unsigned long>(now - last_update_ms_) <= update_interval_ms_) {
        return true;
    }

    uint8_t response[pzem_measures_response_length];

    if (!send_cmd_8(pzem_read_input_registers, 0x0000, 0x000A, false)) {
        invalidate_cache();
        return false;
    }

    if (receive_frame(response, pzem_measures_response_length) != pzem_measures_response_length) {
        invalidate_cache();
        return false;
    }

    cached_measures_.voltage_x10 = static_cast<uint16_t>((static_cast<uint16_t>(response[3]) << 8) | response[4]);
    cached_measures_.current_x1000 = (static_cast<uint32_t>(response[5]) << 8) | static_cast<uint32_t>(response[6]) |
        (static_cast<uint32_t>(response[7]) << 24) | (static_cast<uint32_t>(response[8]) << 16);
    cached_measures_.power_x10 = (static_cast<uint32_t>(response[9]) << 8) | static_cast<uint32_t>(response[10]) |
        (static_cast<uint32_t>(response[11]) << 24) | (static_cast<uint32_t>(response[12]) << 16);
    cached_measures_.energy_wh = (static_cast<uint32_t>(response[13]) << 8) | static_cast<uint32_t>(response[14]) |
        (static_cast<uint32_t>(response[15]) << 24) | (static_cast<uint32_t>(response[16]) << 16);
    cached_measures_.frequency_x10 = static_cast<uint16_t>((static_cast<uint16_t>(response[17]) << 8) | response[18]);
    cached_measures_.power_factor_x100 = static_cast<uint16_t>((static_cast<uint16_t>(response[19]) << 8) | response[20]);
    cached_measures_.alarms = static_cast<uint16_t>((static_cast<uint16_t>(response[21]) << 8) | response[22]);
    cached_measures_.is_connected = true;
    cached_measures_.is_data_valid = true;

    is_cache_valid_ = true;
    last_update_ms_ = now;
    return true;
}

bool Pzem004tRepository::send_cmd_8(uint8_t command, uint16_t register_address, uint16_t value, bool check_response, uint16_t slave_address) {
    uint8_t send_buffer[pzem_cmd_8_length];

    if (slave_address == pzem_invalid_slave_address || slave_address < pzem_min_address || slave_address > pzem_max_address) {
        slave_address = cached_measures_.address;
    }

    send_buffer[0] = static_cast<uint8_t>(slave_address);
    send_buffer[1] = command;
    send_buffer[2] = static_cast<uint8_t>((register_address >> 8) & 0xFF);
    send_buffer[3] = static_cast<uint8_t>(register_address & 0xFF);
    send_buffer[4] = static_cast<uint8_t>((value >> 8) & 0xFF);
    send_buffer[5] = static_cast<uint8_t>(value & 0xFF);
    send_buffer[6] = 0x00;
    send_buffer[7] = 0x00;
    set_crc(send_buffer, pzem_cmd_8_length);

    clear_receive_buffer();
    serial_.write(send_buffer, pzem_cmd_8_length);

    if (!check_response) {
        return true;
    }

    uint8_t response[pzem_cmd_8_length];
    if (receive_frame(response, pzem_cmd_8_length) != pzem_cmd_8_length) {
        return false;
    }

    for (uint8_t i = 0; i < pzem_cmd_8_length; ++i) {
        if (response[i] != send_buffer[i]) {
            return false;
        }
    }

    return true;
}

uint8_t Pzem004tRepository::receive_frame(uint8_t* response, uint8_t expected_length) {
    unsigned long start_ms = get_millis();
    uint8_t index = 0;

    while (index < expected_length && static_cast<unsigned long>(get_millis() - start_ms) < timeout_ms_) {
        if (serial_.available() > 0) {
            int read_value = serial_.read();
            if (read_value >= 0) {
                response[index++] = static_cast<uint8_t>(read_value);
            }
        }
    }

    if (!check_crc(response, index)) {
        cached_measures_.is_connected = false;
        cached_measures_.is_data_valid = false;
        return 0;
    }

    cached_measures_.is_connected = true;
    return index;
}

void Pzem004tRepository::clear_receive_buffer() {
    while (serial_.available() > 0) {
        serial_.read();
    }
}

bool Pzem004tRepository::check_crc(const uint8_t* buffer, uint8_t length) const {
    if (length <= 2) {
        return false;
    }

    uint16_t computed_crc = crc16(buffer, static_cast<uint8_t>(length - 2));
    uint16_t received_crc = static_cast<uint16_t>(buffer[length - 2]) | (static_cast<uint16_t>(buffer[length - 1]) << 8);
    return computed_crc == received_crc;
}

void Pzem004tRepository::set_crc(uint8_t* buffer, uint8_t length) const {
    if (length <= 2) {
        return;
    }

    uint16_t crc = crc16(buffer, static_cast<uint8_t>(length - 2));
    buffer[length - 2] = static_cast<uint8_t>(crc & 0xFF);
    buffer[length - 1] = static_cast<uint8_t>((crc >> 8) & 0xFF);
}

uint16_t Pzem004tRepository::crc16(const uint8_t* data, uint8_t length) const {
    uint16_t crc = 0xFFFF;

    while (length-- > 0) {
        crc ^= static_cast<uint16_t>(*data++);
        for (uint8_t bit_index = 0; bit_index < 8; ++bit_index) {
            if ((crc & 0x0001U) != 0U) {
                crc = static_cast<uint16_t>((crc >> 1) ^ 0xA001U);
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}

unsigned long Pzem004tRepository::get_millis() const {
    return millis();
}

void Pzem004tRepository::invalidate_cache() {
    is_cache_valid_ = false;
    cached_measures_.is_connected = false;
    cached_measures_.is_data_valid = false;
    cached_measures_.current_x1000 = 0UL;
    cached_measures_.power_x10 = 0UL;
    cached_measures_.energy_wh = 0UL;
    cached_measures_.voltage_x10 = 0U;
    cached_measures_.frequency_x10 = 0U;
    cached_measures_.power_factor_x100 = 0U;
    cached_measures_.alarms = 0U;
}
