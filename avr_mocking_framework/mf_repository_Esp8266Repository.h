// mf_repository_Esp8266Repository.h
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <mf_repository_ISerial.h>

struct Esp8266PowerMetrics {
    bool is_device_ready = false;
    bool is_data_valid = false;
    uint16_t voltage_x10 = 0;
    uint32_t current_x1000 = 0;
    uint32_t power_x10 = 0;
    uint32_t energy_wh = 0;
    uint16_t frequency_x10 = 0;
    uint8_t power_factor_x100 = 0;
};

class Esp8266Repository {
public:
    explicit Esp8266Repository(ISerial& serial);
    virtual ~Esp8266Repository();

    virtual void begin(unsigned long baud);
    virtual void set_timeout(unsigned long timeout_ms);
    virtual unsigned long get_timeout() const;

    virtual bool send_power_metrics(const Esp8266PowerMetrics& data);
    virtual bool send_no_data();
    virtual bool send_ping();

    virtual int available();
    virtual int read();
    virtual size_t read_line(char* buffer, size_t max_len);
    virtual void clear_buffer();

protected:
    virtual bool write_char(char value);
    virtual bool write_text(const char* text);
    virtual bool write_uint32(uint32_t value);
    virtual bool write_bool(bool value);

protected:
    ISerial& serial_;
    unsigned long timeout_ms_;
};
