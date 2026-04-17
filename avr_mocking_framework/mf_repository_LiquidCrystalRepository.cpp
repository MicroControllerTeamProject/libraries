#include <mf_repository_LiquidCrystalRepository.h>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystalRepository::LiquidCrystalRepository(uint8_t lcd_addr,
    uint8_t en,
    uint8_t rw,
    uint8_t rs,
    uint8_t d4,
    uint8_t d5,
    uint8_t d6,
    uint8_t d7,
    uint8_t backlight_pin,
    uint8_t backlight_polarity)
    : lcd_addr_(lcd_addr)
    , en_(en)
    , rw_(rw)
    , rs_(rs)
    , d4_(d4)
    , d5_(d5)
    , d6_(d6)
    , d7_(d7)
    , backlight_pin_(backlight_pin)
    , backlight_polarity_(backlight_polarity) {
    rebuild_lcd();
}

LiquidCrystalRepository::~LiquidCrystalRepository() {
    delete lcd_;
}

bool LiquidCrystalRepository::try_detect_i2c_address(uint8_t* detected_address) {
    Wire.begin();

    for (uint8_t address = 0x03; address < 0x78; ++address) {
        if (is_i2c_device_available(address)) {
            if (detected_address != nullptr) {
                *detected_address = address;
            }
            return true;
        }
    }

    if (detected_address != nullptr) {
        *detected_address = 0;
    }

    return false;
}

bool LiquidCrystalRepository::is_i2c_device_available(uint8_t i2c_address) {
    Wire.begin();
    Wire.beginTransmission(i2c_address);
    return Wire.endTransmission() == 0;
}

bool LiquidCrystalRepository::is_configured_i2c_device_available() {
    return is_i2c_device_available(lcd_addr_);
}

void LiquidCrystalRepository::use_i2c_address(uint8_t lcd_addr) {
    lcd_addr_ = lcd_addr;
    is_initialized_ = false;
    rebuild_lcd();
}

uint8_t LiquidCrystalRepository::get_i2c_address() {
    return lcd_addr_;
}

void LiquidCrystalRepository::begin(uint8_t cols, uint8_t rows) {
    Wire.begin();
    if (lcd_ == nullptr) {
        rebuild_lcd();
    }
    lcd_->begin(cols, rows);
    cols_ = cols;
    rows_ = rows;
    is_initialized_ = true;
}

void LiquidCrystalRepository::clear() {
    lcd_->clear();
}

void LiquidCrystalRepository::home() {
    lcd_->home();
}

void LiquidCrystalRepository::set_cursor(uint8_t col, uint8_t row) {
    lcd_->setCursor(col, row);
}

void LiquidCrystalRepository::print(const char* data) {
    lcd_->print(data);
}

void LiquidCrystalRepository::print(char data) {
    lcd_->print(data);
}

void LiquidCrystalRepository::print(int32_t data) {
    lcd_->print((long)data);
}

void LiquidCrystalRepository::print(uint8_t data) {
    lcd_->print(data);
}

void LiquidCrystalRepository::print(float data, uint8_t precision) {
    lcd_->print(data, precision);
}

void LiquidCrystalRepository::write(uint8_t data) {
    lcd_->write(data);
}

void LiquidCrystalRepository::backlight_on() {
    lcd_->backlight();
}

void LiquidCrystalRepository::backlight_off() {
    lcd_->noBacklight();
}

void LiquidCrystalRepository::display_on() {
    lcd_->display();
}

void LiquidCrystalRepository::display_off() {
    lcd_->noDisplay();
}

void LiquidCrystalRepository::cursor_on() {
    lcd_->cursor();
}

void LiquidCrystalRepository::cursor_off() {
    lcd_->noCursor();
}

void LiquidCrystalRepository::blink_on() {
    lcd_->blink();
}

void LiquidCrystalRepository::blink_off() {
    lcd_->noBlink();
}

void LiquidCrystalRepository::scroll_left() {
    lcd_->scrollDisplayLeft();
}

void LiquidCrystalRepository::scroll_right() {
    lcd_->scrollDisplayRight();
}

void LiquidCrystalRepository::autoscroll_on() {
    lcd_->autoscroll();
}

void LiquidCrystalRepository::autoscroll_off() {
    lcd_->noAutoscroll();
}

uint8_t LiquidCrystalRepository::get_cols() {
    return cols_;
}

uint8_t LiquidCrystalRepository::get_rows() {
    return rows_;
}

bool LiquidCrystalRepository::is_initialized() {
    return is_initialized_;
}

void LiquidCrystalRepository::rebuild_lcd() {
    delete lcd_;
    lcd_ = new LiquidCrystal_I2C(
        lcd_addr_,
        en_,
        rw_,
        rs_,
        d4_,
        d5_,
        d6_,
        d7_,
        backlight_pin_,
        (t_backlighPol)backlight_polarity_);
}
