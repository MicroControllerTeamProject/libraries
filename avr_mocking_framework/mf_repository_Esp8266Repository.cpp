// mf_repository_Esp8266Repository.cpp
#include <mf_repository_Esp8266Repository.h>

namespace {
constexpr unsigned long esp8266_default_timeout_ms = 50UL;
}

Esp8266Repository::Esp8266Repository(ISerial& serial)
    : serial_(serial), timeout_ms_(esp8266_default_timeout_ms) {
}

Esp8266Repository::~Esp8266Repository() {
}

void Esp8266Repository::begin(unsigned long baud) {
    serial_.begin(baud);
    serial_.setTimeout(timeout_ms_);
}

void Esp8266Repository::set_timeout(unsigned long timeout_ms) {
    timeout_ms_ = timeout_ms;
    serial_.setTimeout(timeout_ms_);
}

unsigned long Esp8266Repository::get_timeout() const {
    return timeout_ms_;
}

bool Esp8266Repository::send_power_metrics(const Esp8266PowerMetrics& data) {
    if (!write_char('M')) return false;
    if (!write_char(',')) return false;
    if (!write_bool(data.is_device_ready)) return false;
    if (!write_char(',')) return false;
    if (!write_bool(data.is_data_valid)) return false;
    if (!write_char(',')) return false;
    if (!write_uint32(data.voltage_x10)) return false;
    if (!write_char(',')) return false;
    if (!write_uint32(data.current_x1000)) return false;
    if (!write_char(',')) return false;
    if (!write_uint32(data.power_x10)) return false;
    if (!write_char(',')) return false;
    if (!write_uint32(data.energy_wh)) return false;
    if (!write_char(',')) return false;
    if (!write_uint32(data.frequency_x10)) return false;
    if (!write_char(',')) return false;
    if (!write_uint32(data.power_factor_x100)) return false;
    return write_char('\n');
}

bool Esp8266Repository::send_no_data() {
    Esp8266PowerMetrics data;
    data.is_device_ready = false;
    data.is_data_valid = false;
    return send_power_metrics(data);
}

bool Esp8266Repository::send_ping() {
    if (!write_char('P')) return false;
    return write_char('\n');
}

int Esp8266Repository::available() {
    return serial_.available();
}

int Esp8266Repository::read() {
    return serial_.read();
}

size_t Esp8266Repository::read_line(char* buffer, size_t max_len) {
    if (buffer == 0 || max_len < 2) {
        return 0;
    }

    size_t read_len = serial_.readBytesUntil('\n', buffer, max_len - 1);
    buffer[read_len] = '\0';

    if (read_len > 0 && buffer[read_len - 1] == '\r') {
        buffer[read_len - 1] = '\0';
        --read_len;
    }

    return read_len;
}

void Esp8266Repository::clear_buffer() {
    while (serial_.available() > 0) {
        serial_.read();
    }
}

bool Esp8266Repository::write_char(char value) {
    return serial_.write(static_cast<uint8_t>(value)) == 1;
}

bool Esp8266Repository::write_text(const char* text) {
    if (text == 0) {
        return false;
    }
    return serial_.write(text) > 0;
}

bool Esp8266Repository::write_uint32(uint32_t value) {
    char digits[10];
    uint8_t count = 0;

    if (value == 0) {
        return write_char('0');
    }

    while (value > 0 && count < sizeof(digits)) {
        digits[count++] = static_cast<char>('0' + (value % 10));
        value /= 10;
    }

    while (count > 0) {
        if (!write_char(digits[--count])) {
            return false;
        }
    }

    return true;
}

bool Esp8266Repository::write_bool(bool value) {
    return write_char(value ? '1' : '0');
}
