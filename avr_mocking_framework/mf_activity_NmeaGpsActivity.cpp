// mf_activity_NmeaGpsActivity.cpp
#include <mf_activity_NmeaGpsActivity.h>

mf_activity_NmeaGpsActivity::mf_activity_NmeaGpsActivity(mf_repository_NmeaGpsRepository& nmea_gps_repository)
    : nmea_gps_repository_(nmea_gps_repository) {
}

bool mf_activity_NmeaGpsActivity::try_read_data(NmeaGpsData& out_data, uint8_t max_sentences_to_read) {
    NmeaGpsData data = {};
    clear_data(data);
    bool parsed_any_sentence = false;
    char sentence[nmea_sentence_buffer_length];
    for (uint8_t sentence_index = 0; sentence_index < max_sentences_to_read; ++sentence_index) {
        if (!nmea_gps_repository_.read_sentence(sentence, nmea_sentence_buffer_length)) {
            continue;
        }
        if (parse_sentence(sentence, data)) {
            parsed_any_sentence = true;
        }
    }
    if (!parsed_any_sentence) {
        return false;
    }
    out_data = data;
    return true;
}

bool mf_activity_NmeaGpsActivity::parse_sentence(const char* sentence, NmeaGpsData& data) const {
    if (is_sentence_type(sentence, 'G', 'G', 'A')) {
        return parse_gga_sentence(sentence, data);
    }

    if (is_sentence_type(sentence, 'R', 'M', 'C')) {
        return parse_rmc_sentence(sentence, data);
    }

    if (is_sentence_type(sentence, 'V', 'T', 'G')) {
        return parse_vtg_sentence(sentence, data);
    }

    return false;
}

bool mf_activity_NmeaGpsActivity::parse_gga_sentence(const char* sentence, NmeaGpsData& data) const {
    const char* field = nullptr;
    uint8_t length = 0;

    if (get_field(sentence, 1, field, length)) {
        parse_time_field(field, length, data);
    }

    uint16_t fix_quality = 0;
    if (!get_field(sentence, 6, field, length) || !parse_uint_field(field, length, fix_quality)) {
        return false;
    }

    data.fix_quality = static_cast<uint8_t>(fix_quality);
    data.has_fix = fix_quality > 0;

    uint16_t satellites = 0;
    if (get_field(sentence, 7, field, length) && parse_uint_field(field, length, satellites)) {
        data.satellites = static_cast<uint8_t>(satellites);
    }

    int32_t altitude_meters_x10 = 0;
    if (get_field(sentence, 9, field, length) && parse_decimal_scaled(field, length, 1, altitude_meters_x10)) {
        data.altitude_meters_x10 = altitude_meters_x10;
        data.has_altitude = true;
    }

    if (!data.has_fix) {
        return true;
    }

    const char* latitude_field = nullptr;
    const char* longitude_field = nullptr;
    const char* ns_field = nullptr;
    const char* ew_field = nullptr;
    uint8_t latitude_length = 0;
    uint8_t longitude_length = 0;
    uint8_t ns_length = 0;
    uint8_t ew_length = 0;

    if (!get_field(sentence, 2, latitude_field, latitude_length) || !get_field(sentence, 3, ns_field, ns_length)) {
        return true;
    }

    if (!get_field(sentence, 4, longitude_field, longitude_length) || !get_field(sentence, 5, ew_field, ew_length)) {
        return true;
    }

    int32_t latitude_x1000000 = 0;
    int32_t longitude_x1000000 = 0;

    if (ns_length == 1 && ew_length == 1 && parse_coordinate_field(latitude_field, latitude_length, ns_field[0], 2, latitude_x1000000) && parse_coordinate_field(longitude_field, longitude_length, ew_field[0], 3, longitude_x1000000)) {
        data.latitude_x1000000 = latitude_x1000000;
        data.longitude_x1000000 = longitude_x1000000;
        data.has_position = true;
    }

    return true;
}

bool mf_activity_NmeaGpsActivity::parse_rmc_sentence(const char* sentence, NmeaGpsData& data) const {
    const char* field = nullptr;
    uint8_t length = 0;

    if (get_field(sentence, 1, field, length)) {
        parse_time_field(field, length, data);
    }

    if (get_field(sentence, 9, field, length)) {
        parse_date_field(field, length, data);
    }

    if (!get_field(sentence, 2, field, length) || length != 1) {
        return false;
    }

    data.has_fix = field[0] == 'A';

    if (!data.has_fix) {
        return true;
    }

    const char* latitude_field = nullptr;
    const char* longitude_field = nullptr;
    const char* ns_field = nullptr;
    const char* ew_field = nullptr;
    uint8_t latitude_length = 0;
    uint8_t longitude_length = 0;
    uint8_t ns_length = 0;
    uint8_t ew_length = 0;

    if (get_field(sentence, 3, latitude_field, latitude_length) && get_field(sentence, 4, ns_field, ns_length) && get_field(sentence, 5, longitude_field, longitude_length) && get_field(sentence, 6, ew_field, ew_length)) {
        int32_t latitude_x1000000 = 0;
        int32_t longitude_x1000000 = 0;

        if (ns_length == 1 && ew_length == 1 && parse_coordinate_field(latitude_field, latitude_length, ns_field[0], 2, latitude_x1000000) && parse_coordinate_field(longitude_field, longitude_length, ew_field[0], 3, longitude_x1000000)) {
            data.latitude_x1000000 = latitude_x1000000;
            data.longitude_x1000000 = longitude_x1000000;
            data.has_position = true;
        }
    }

    int32_t speed_knots_x100 = 0;
    if (get_field(sentence, 7, field, length) && parse_decimal_scaled(field, length, 2, speed_knots_x100) && speed_knots_x100 >= 0) {
        uint32_t speed_kmh_x100 = static_cast<uint32_t>(speed_knots_x100) * 1852UL;
        data.speed_kmh_x100 = static_cast<uint16_t>((speed_kmh_x100 + 500UL) / 1000UL);
        data.has_speed = true;
    }

    return true;
}

bool mf_activity_NmeaGpsActivity::parse_vtg_sentence(const char* sentence, NmeaGpsData& data) const {
    const char* field = nullptr;
    uint8_t length = 0;

    int32_t speed_kmh_x100 = 0;
    if (!get_field(sentence, 7, field, length) || !parse_decimal_scaled(field, length, 2, speed_kmh_x100) || speed_kmh_x100 < 0) {
        return false;
    }

    data.speed_kmh_x100 = static_cast<uint16_t>(speed_kmh_x100);
    data.has_speed = true;
    return true;
}

bool mf_activity_NmeaGpsActivity::is_sentence_type(const char* sentence, char first, char second, char third) const {
    return sentence != nullptr && sentence[0] == '$' && sentence[3] == first && sentence[4] == second && sentence[5] == third;
}

bool mf_activity_NmeaGpsActivity::get_field(const char* sentence, uint8_t field_index, const char*& field, uint8_t& length) const {
    if (sentence == nullptr) {
        return false;
    }

    const char* current = sentence;
    if (*current == '$') {
        ++current;
    }

    const char* field_start = current;
    uint8_t current_field_index = 0;

    while (*current != '\0') {
        if (*current == ',' || *current == '*') {
            if (current_field_index == field_index) {
                field = field_start;
                length = static_cast<uint8_t>(current - field_start);
                return true;
            }

            if (*current == '*') {
                return false;
            }

            ++current_field_index;
            field_start = current + 1;
        }

        ++current;
    }

    return false;
}

bool mf_activity_NmeaGpsActivity::parse_uint_field(const char* field, uint8_t length, uint16_t& out_value) const {
    if (field == nullptr || length == 0) {
        return false;
    }

    uint16_t value = 0;

    for (uint8_t index = 0; index < length; ++index) {
        if (field[index] < '0' || field[index] > '9') {
            return false;
        }

        value = static_cast<uint16_t>((value * 10U) + static_cast<uint16_t>(field[index] - '0'));
    }

    out_value = value;
    return true;
}

bool mf_activity_NmeaGpsActivity::parse_decimal_scaled(const char* field, uint8_t length, uint8_t scale_digits, int32_t& out_value) const {
    if (field == nullptr || length == 0) {
        return false;
    }

    bool is_negative = false;
    bool has_digit = false;
    bool has_decimal_separator = false;
    uint8_t fraction_digits = 0;
    int32_t value = 0;
    uint8_t index = 0;

    if (field[0] == '-') {
        is_negative = true;
        index = 1;
    }

    for (; index < length; ++index) {
        char current_char = field[index];

        if (current_char == '.') {
            if (has_decimal_separator) {
                return false;
            }

            has_decimal_separator = true;
            continue;
        }

        if (current_char < '0' || current_char > '9') {
            return false;
        }

        has_digit = true;

        if (!has_decimal_separator || fraction_digits < scale_digits) {
            value = (value * 10L) + static_cast<int32_t>(current_char - '0');
        }

        if (has_decimal_separator && fraction_digits < scale_digits) {
            ++fraction_digits;
        }
    }

    if (!has_digit) {
        return false;
    }

    while (fraction_digits < scale_digits) {
        value *= 10L;
        ++fraction_digits;
    }

    out_value = is_negative ? -value : value;
    return true;
}

bool mf_activity_NmeaGpsActivity::parse_time_field(const char* field, uint8_t length, NmeaGpsData& data) const {
    if (length < 6) {
        return false;
    }

    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t second = 0;

    if (!parse_two_digits(field, length, 0, hour) || !parse_two_digits(field, length, 2, minute) || !parse_two_digits(field, length, 4, second)) {
        return false;
    }

    if (hour > 23 || minute > 59 || second > 59) {
        return false;
    }

    data.hour = hour;
    data.minute = minute;
    data.second = second;
    data.has_time = true;
    return true;
}

bool mf_activity_NmeaGpsActivity::parse_date_field(const char* field, uint8_t length, NmeaGpsData& data) const {
    if (length != 6) {
        return false;
    }
    uint8_t day = 0;
    uint8_t month = 0;
    uint8_t year = 0;
    if (!parse_two_digits(field, length, 0, day) || !parse_two_digits(field, length, 2, month) || !parse_two_digits(field, length, 4, year)) {
        return false;
    }
    if (day < 1 || day > 31 || month < 1 || month > 12) {
        return false;
    }
    data.day = day;
    data.month = month;
    data.year = static_cast<uint16_t>(2000U + year);
    data.has_date = true;
    return true;
}

bool mf_activity_NmeaGpsActivity::parse_coordinate_field(const char* field, uint8_t length, char hemisphere, uint8_t degree_digits, int32_t& out_value) const {
    if (field == nullptr || length <= degree_digits) {
        return false;
    }

    uint16_t degrees = 0;
    for (uint8_t index = 0; index < degree_digits; ++index) {
        if (field[index] < '0' || field[index] > '9') {
            return false;
        }

        degrees = static_cast<uint16_t>((degrees * 10U) + static_cast<uint16_t>(field[index] - '0'));
    }

    int32_t minutes_x100000 = 0;
    if (!parse_decimal_scaled(field + degree_digits, static_cast<uint8_t>(length - degree_digits), 5, minutes_x100000) || minutes_x100000 < 0) {
        return false;
    }

    int32_t coordinate_x1000000 = static_cast<int32_t>(degrees) * 1000000L;
    coordinate_x1000000 += static_cast<int32_t>((minutes_x100000 + 3L) / 6L);

    if (hemisphere == 'S' || hemisphere == 'W') {
        coordinate_x1000000 = -coordinate_x1000000;
    } else if (hemisphere != 'N' && hemisphere != 'E') {
        return false;
    }

    out_value = coordinate_x1000000;
    return true;
}

bool mf_activity_NmeaGpsActivity::parse_two_digits(const char* field, uint8_t length, uint8_t index, uint8_t& out_value) const {
    if (field == nullptr || static_cast<uint8_t>(index + 1) >= length) {
        return false;
    }

    if (field[index] < '0' || field[index] > '9' || field[index + 1] < '0' || field[index + 1] > '9') {
        return false;
    }

    out_value = static_cast<uint8_t>(((field[index] - '0') * 10) + (field[index + 1] - '0'));
    return true;
}

void mf_activity_NmeaGpsActivity::clear_data(NmeaGpsData& data) const {
    data.has_fix = false;
    data.has_position = false;
    data.has_time = false;
    data.has_date = false;
    data.has_speed = false;
    data.has_altitude = false;
    data.latitude_x1000000 = 0L;
    data.longitude_x1000000 = 0L;
    data.altitude_meters_x10 = 0L;
    data.speed_kmh_x100 = 0U;
    data.year = 0U;
    data.month = 0U;
    data.day = 0U;
    data.hour = 0U;
    data.minute = 0U;
    data.second = 0U;
    data.satellites = 0U;
    data.fix_quality = 0U;
}
