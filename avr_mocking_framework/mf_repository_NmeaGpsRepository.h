// mf_repository_NmeaGpsRepository.h
#pragma once

#include <stdint.h>
#include <mf_repository_ISerial.h>

class mf_repository_NmeaGpsRepository {
public:
    // Inizializza il repository con l'interfaccia seriale concreta.
    explicit mf_repository_NmeaGpsRepository(ISerial& serial);
    virtual ~mf_repository_NmeaGpsRepository() = default;

    // Avvia la seriale GPS con baud rate di default e pulisce il buffer.
    virtual void begin();
    // Aggiorna il timeout di lettura usato dalla seriale.
    virtual void set_timeout(unsigned long timeout_ms);
    // Legge una frase NMEA completa e la valida tramite checksum.
    virtual bool read_sentence(char* out_sentence, uint8_t max_length);

private:
    // Verifica checksum e formato base della frase NMEA ricevuta.
    bool is_sentence_checksum_valid(const char* sentence) const;
    // Converte un carattere esadecimale nel relativo nibble.
    int8_t hex_to_nibble(char value) const;
    // Punto unico per leggere il tempo corrente in millisecondi.
    unsigned long get_millis() const;
    // Svuota eventuali byte residui nel buffer seriale.
    void clear_receive_buffer();

private:
    ISerial& serial_;
    unsigned long timeout_ms_;
};
