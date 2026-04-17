#pragma once
#include <stdint.h>

class LiquidCrystal_I2C;

class LiquidCrystalRepository {
public:
    LiquidCrystalRepository(uint8_t lcd_addr,
        uint8_t en,
        uint8_t rw,
        uint8_t rs,
        uint8_t d4,
        uint8_t d5,
        uint8_t d6,
        uint8_t d7,
        uint8_t backlight_pin,
        uint8_t backlight_polarity);
    virtual ~LiquidCrystalRepository();
    virtual bool try_detect_i2c_address(uint8_t* detected_address);
    virtual bool is_i2c_device_available(uint8_t i2c_address);
    virtual bool is_configured_i2c_device_available();
    virtual void use_i2c_address(uint8_t lcd_addr);
    virtual uint8_t get_i2c_address();
    virtual void begin(uint8_t cols, uint8_t rows);
    virtual void clear();
    virtual void home();
    virtual void set_cursor(uint8_t col, uint8_t row);
    virtual void print(const char* data);
    virtual void print(char data);
    virtual void print(int32_t data);
    virtual void print(uint8_t data);
    virtual void print(float data, uint8_t precision = 2);
    virtual void write(uint8_t data);
    virtual void backlight_on();
    virtual void backlight_off();
    virtual void display_on();
    virtual void display_off();
    virtual void cursor_on();
    virtual void cursor_off();
    virtual void blink_on();
    virtual void blink_off();
    virtual void scroll_left();
    virtual void scroll_right();
    virtual void autoscroll_on();
    virtual void autoscroll_off();
    virtual uint8_t get_cols();
    virtual uint8_t get_rows();
    virtual bool is_initialized();
private:
    void rebuild_lcd();
    LiquidCrystal_I2C* lcd_ = nullptr;
    uint8_t lcd_addr_ = 0;
    uint8_t en_ = 0;
    uint8_t rw_ = 0;
    uint8_t rs_ = 0;
    uint8_t d4_ = 0;
    uint8_t d5_ = 0;
    uint8_t d6_ = 0;
    uint8_t d7_ = 0;
    uint8_t backlight_pin_ = 0;
    uint8_t backlight_polarity_ = 0;
    uint8_t cols_ = 0;
    uint8_t rows_ = 0;
    bool is_initialized_ = false;
};
