// mf_activity_NmeaGpsActivity.h
#pragma once

#include <stdint.h>
#include <mf_repository_NmeaGpsRepository.h>

struct NmeaGpsData {
    bool has_fix;
    bool has_position;
    bool has_time;
    bool has_date;
    bool has_speed;
    bool has_altitude;
    int32_t latitude_x1000000;
    int32_t longitude_x1000000;
    int32_t altitude_meters_x10;
    uint16_t speed_kmh_x100;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t satellites;
    uint8_t fix_quality;
};

class mf_activity_NmeaGpsActivity {
public:
    // Collega l'activity al repository che legge le frasi NMEA.
    explicit mf_activity_NmeaGpsActivity(mf_repository_NmeaGpsRepository& nmea_gps_repository);
    virtual ~mf_activity_NmeaGpsActivity() = default;

    // Legge piu frasi NMEA, le interpreta e costruisce un NmeaGpsData coerente.
    virtual bool try_read_data(NmeaGpsData& out_data, uint8_t max_sentences_to_read = 6);

private:
    static const uint8_t nmea_sentence_buffer_length = 83;

    // Smista la frase NMEA verso il parser specifico in base al tipo (GGA/RMC/VTG).
    bool parse_sentence(const char* sentence, NmeaGpsData& data) const;
    // Estrae fix, satelliti, altitudine e coordinate da una frase GGA.
    bool parse_gga_sentence(const char* sentence, NmeaGpsData& data) const;
    // Estrae fix, coordinate, velocita in nodi e data/ora da una frase RMC.
    bool parse_rmc_sentence(const char* sentence, NmeaGpsData& data) const;
    // Estrae la velocita in km/h da una frase VTG.
    bool parse_vtg_sentence(const char* sentence, NmeaGpsData& data) const;
    // Verifica che la frase inizi con il tipo atteso.
    bool is_sentence_type(const char* sentence, char first, char second, char third) const;
    // Recupera un campo NMEA per indice e ne restituisce puntatore/lunghezza.
    bool get_field(const char* sentence, uint8_t field_index, const char*& field, uint8_t& length) const;
    // Converte un campo numerico intero in uint16_t.
    bool parse_uint_field(const char* field, uint8_t length, uint16_t& out_value) const;
    // Converte un campo decimale in intero scalato con il numero di cifre richiesto.
    bool parse_decimal_scaled(const char* field, uint8_t length, uint8_t scale_digits, int32_t& out_value) const;
    // Converte il campo ora hhmmss nei campi ora/minuto/secondo della struct.
    bool parse_time_field(const char* field, uint8_t length, NmeaGpsData& data) const;
    // Converte il campo data ddmmyy in giorno/mese/anno.
    bool parse_date_field(const char* field, uint8_t length, NmeaGpsData& data) const;
    // Converte coordinate NMEA (gradi+minuti) nel formato gradi x 1.000.000.
    bool parse_coordinate_field(const char* field, uint8_t length, char hemisphere, uint8_t degree_digits, int32_t& out_value) const;
    // Legge due cifre in posizione nota e le converte in un byte.
    bool parse_two_digits(const char* field, uint8_t length, uint8_t index, uint8_t& out_value) const;
    // Azzera tutti i campi di output prima di iniziare un nuovo parsing.
    void clear_data(NmeaGpsData& data) const;

private:
    mf_repository_NmeaGpsRepository& nmea_gps_repository_;
};
