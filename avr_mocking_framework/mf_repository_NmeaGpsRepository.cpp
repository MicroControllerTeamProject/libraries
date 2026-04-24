// mf_repository_NmeaGpsRepository.cpp
#include <mf_repository_NmeaGpsRepository.h>
#include <Arduino.h>

namespace {
constexpr unsigned long nmea_gps_default_baud_rate = 9600UL;
constexpr unsigned long nmea_gps_default_timeout_ms = 1000UL;
constexpr uint8_t nmea_min_sentence_length = 7;
constexpr uint8_t nmea_checksum_chars = 2;
}

mf_repository_NmeaGpsRepository::mf_repository_NmeaGpsRepository(ISerial& serial)
    : serial_(serial), timeout_ms_(nmea_gps_default_timeout_ms) {
}

void mf_repository_NmeaGpsRepository::begin() {
    serial_.begin(nmea_gps_default_baud_rate);
    serial_.setTimeout(timeout_ms_);
    clear_receive_buffer();
}

void mf_repository_NmeaGpsRepository::set_timeout(unsigned long timeout_ms) {
    timeout_ms_ = timeout_ms;
    serial_.setTimeout(timeout_ms_);
}

bool mf_repository_NmeaGpsRepository::read_sentence(char* out_sentence, uint8_t max_length) {
    if (out_sentence == nullptr || max_length < nmea_min_sentence_length) {
        return false;
    }

    unsigned long start_ms = get_millis();
    uint8_t index = 0;
    bool sentence_started = false;

    while (static_cast<unsigned long>(get_millis() - start_ms) < timeout_ms_) {
        if (serial_.available() <= 0) {
            continue;
        }

        int read_value = serial_.read();
        if (read_value < 0) {
            continue;
        }

        char current_char = static_cast<char>(read_value);

        if (current_char == '$') {
            sentence_started = true;
            index = 0;
            out_sentence[index++] = current_char;
            continue;
        }

        if (!sentence_started) {
            continue;
        }

        if (current_char == '\r') {
            continue;
        }

        if (current_char == '\n') {
            out_sentence[index] = '\0';
            return is_sentence_checksum_valid(out_sentence);
        }

        if (index >= static_cast<uint8_t>(max_length - 1)) {
            out_sentence[0] = '\0';
            return false;
        }

        out_sentence[index++] = current_char;
    }

    out_sentence[0] = '\0';
    return false;
}

bool mf_repository_NmeaGpsRepository::is_sentence_checksum_valid(const char* sentence) const {
    if (sentence == nullptr || sentence[0] != '$') {
        return false;
    }

    uint8_t checksum = 0;
    uint8_t index = 1;

    while (sentence[index] != '\0' && sentence[index] != '*') {
        checksum ^= static_cast<uint8_t>(sentence[index]);
        ++index;
    }

    if (sentence[index] != '*') {
        return false;
    }

    int8_t high_nibble = hex_to_nibble(sentence[index + 1]);
    int8_t low_nibble = hex_to_nibble(sentence[index + 2]);

    if (high_nibble < 0 || low_nibble < 0) {
        return false;
    }

    if (sentence[index + 1 + nmea_checksum_chars] != '\0') {
        return false;
    }

    uint8_t received_checksum = static_cast<uint8_t>((static_cast<uint8_t>(high_nibble) << 4) | static_cast<uint8_t>(low_nibble));
    return checksum == received_checksum;
}

int8_t mf_repository_NmeaGpsRepository::hex_to_nibble(char value) const {
    if (value >= '0' && value <= '9') {
        return static_cast<int8_t>(value - '0');
    }

    if (value >= 'A' && value <= 'F') {
        return static_cast<int8_t>(value - 'A' + 10);
    }

    if (value >= 'a' && value <= 'f') {
        return static_cast<int8_t>(value - 'a' + 10);
    }

    return -1;
}

unsigned long mf_repository_NmeaGpsRepository::get_millis() const {
    return millis();
}

void mf_repository_NmeaGpsRepository::clear_receive_buffer() {
    while (serial_.available() > 0) {
        serial_.read();
    }
}
