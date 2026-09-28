// File: mf_repository_LiquidCrystalRepository.h
#pragma once
#include <stdint.h>

class LiquidCrystal_I2C;

class LiquidCrystalRepository {
public:
    LiquidCrystalRepository(uint8_t lcd_addr, uint8_t en, uint8_t rw, uint8_t rs, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t backlight_pin, uint8_t backlight_polarity);
    virtual ~LiquidCrystalRepository();

    virtual bool try_detect_i2c_address(uint8_t* detected_address);
    virtual bool is_i2c_device_available(uint8_t i2c_address);
    virtual bool is_configured_i2c_device_available();
    virtual void use_i2c_address(uint8_t lcd_addr);
    virtual uint8_t get_i2c_address();

    virtual void configure(uint8_t cols = 16, uint8_t rows = 2, bool enable_backlight = true, bool clear_before_use = true);
    virtual void display_text_at(uint8_t col, uint8_t row, const char* message, bool clear_before = false);
    virtual void display_label_value_at(uint8_t col, uint8_t row, const char* label, float value, uint8_t precision = 2, bool clear_before = false);
    virtual void display_two_rows(const char* first_row, const char* second_row, bool clear_before = true);
    virtual void display_rows(const char* const* row_text_list, uint8_t row_count, bool clear_before = true);
    virtual void show_temporary_message(uint8_t col, uint8_t row, const char* message, unsigned long hold_ms, bool clear_before = true, bool clear_after = true);
    virtual void scroll_text_left(uint8_t row, const char* message, unsigned long step_delay_ms = 250, bool clear_before = true);

    virtual uint8_t get_cols();
    virtual uint8_t get_rows();
    virtual bool is_initialized();

private:
    void rebuild_lcd();
    void begin(uint8_t cols, uint8_t rows);
    void clear_display();
    void set_cursor(uint8_t col, uint8_t row);
    void print_raw(const char* data);
    void print_raw(char data);
    void print_raw(int32_t data);
    void print_raw(uint8_t data);
    void print_raw(float data, uint8_t precision = 2);
    void backlight_on();
    void backlight_off();
    uint8_t clamp_row(uint8_t row);
    uint8_t clamp_col(uint8_t col);
    void print_trimmed(const char* message, uint8_t max_chars);
    void render_row(uint8_t row, const char* message);

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