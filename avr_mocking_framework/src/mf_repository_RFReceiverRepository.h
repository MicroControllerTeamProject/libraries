#pragma once
#include <stdint.h>

class RFReceiverRepository {
public:
    RFReceiverRepository(uint8_t rx_pin,
        uint8_t ptt_pin,
        uint16_t vw_speed,
        uint8_t* userBuf,
        uint8_t  userBufLen);

    bool begin();
    void stop();

    // In/Out: *inoutLen = cap in ingresso, lunghezza reale in uscita.
    // Ritorna true se messaggio ricevuto con CRC ok.
    bool read(uint8_t* out, uint8_t* inoutLen);

private:
    uint8_t  _rx_pin;
    uint8_t  _ptt_pin;
    uint16_t _vw_speed;
    uint8_t* _buf;
    uint8_t  _bufLen;
};
