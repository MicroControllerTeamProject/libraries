
#include <mf_repository_RFReceiverRepository.h>
#include <VirtualWire.h>

RFReceiverRepository::RFReceiverRepository(uint8_t rx_pin,
    uint8_t ptt_pin,
    uint16_t vw_speed,
    uint8_t* userBuf,
    uint8_t  userBufLen)
    : _rx_pin(rx_pin),
    _ptt_pin(ptt_pin),
    _vw_speed(vw_speed),
    _buf(userBuf),
    _bufLen(userBufLen)
{
}

bool RFReceiverRepository::begin() {
    if (_buf == 0 || _bufLen == 0) return false;
    vw_set_ptt_pin(_ptt_pin);
    vw_set_ptt_inverted(false);
    vw_set_rx_pin(_rx_pin);
    vw_setup(_vw_speed);   // VirtualWire tipicamente è void
    vw_rx_start();
    return true;
}

void RFReceiverRepository::stop() {
    vw_rx_stop();
}

bool RFReceiverRepository::read(uint8_t* out, uint8_t* inoutLen) {
    if (!out || !inoutLen || *inoutLen == 0) return false;
    uint8_t len = _bufLen;                 // cap interno
    if (vw_get_message(_buf, &len)) {      // CRC ok
        uint8_t n = (len <= *inoutLen) ? len : *inoutLen;
        for (uint8_t i = 0; i < n; ++i) out[i] = _buf[i];
        *inoutLen = n;
        return true;
    }
    return false;
}
