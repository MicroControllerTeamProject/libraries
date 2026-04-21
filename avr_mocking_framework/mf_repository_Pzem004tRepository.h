// mf_repository_Pzem004tRepository.h
#pragma once

#include <stdint.h>
#include <mf_repository_ISerial.h>

struct Pzem004tMeasures {
    uint32_t current_x1000;
    uint32_t power_x10;
    uint32_t energy_wh;
    uint16_t voltage_x10;
    uint16_t frequency_x10;
    uint16_t power_factor_x100;
    uint16_t alarms;
    uint8_t address;
    bool is_connected;
    bool is_data_valid;
};

class Pzem004tRepository {
public:
    explicit Pzem004tRepository(ISerial& serial, uint8_t address = 0xF8);
    virtual ~Pzem004tRepository() = default;

    virtual void begin();
    virtual void set_timeout(unsigned long timeout_ms);
    virtual unsigned long get_timeout() const;
    virtual void set_update_interval(unsigned long update_interval_ms);
    virtual unsigned long get_update_interval() const;

    virtual bool read_measures(Pzem004tMeasures& out_measures);
    virtual bool reset_energy();
    virtual bool set_power_alarm(uint16_t watts);
    virtual bool set_address(uint8_t address);
    virtual uint8_t read_address(bool update_internal_address = false);
    virtual uint8_t get_address() const;
    virtual bool is_connected() const;

protected:
    virtual bool update_cache();
    virtual bool send_cmd_8(uint8_t command, uint16_t register_address, uint16_t value, bool check_response = false, uint16_t slave_address = 0xFFFF);
    virtual uint8_t receive_frame(uint8_t* response, uint8_t expected_length);
    virtual void clear_receive_buffer();
    virtual bool check_crc(const uint8_t* buffer, uint8_t length) const;
    virtual void set_crc(uint8_t* buffer, uint8_t length) const;
    virtual uint16_t crc16(const uint8_t* data, uint8_t length) const;
    virtual unsigned long get_millis() const;
    virtual void invalidate_cache();

protected:
    ISerial& serial_;
    Pzem004tMeasures cached_measures_;
    unsigned long timeout_ms_;
    unsigned long update_interval_ms_;
    unsigned long last_update_ms_;
    bool is_cache_valid_;
};
