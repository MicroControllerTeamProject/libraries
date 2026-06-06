// File: mf_repository_LiquidCrystalRepository.cpp
#include <mf_repository_LiquidCrystalRepository.h>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

LiquidCrystalRepository::LiquidCrystalRepository(uint8_t lcd_addr, uint8_t en, uint8_t rw, uint8_t rs, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t backlight_pin, uint8_t backlight_polarity)
    : lcd_addr_(lcd_addr), en_(en), rw_(rw), rs_(rs), d4_(d4), d5_(d5), d6_(d6), d7_(d7), backlight_pin_(backlight_pin), backlight_polarity_(backlight_polarity) {
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

void LiquidCrystalRepository::configure(uint8_t cols, uint8_t rows, bool enable_backlight, bool clear_before_use) {
    if (cols == 0) cols = 16;
    if (rows == 0) rows = 2;

    begin(cols, rows);

    if (enable_backlight) {
        backlight_on();
    }
    else {
        backlight_off();
    }

    if (clear_before_use) {
        clear_display();
    }
}
void LiquidCrystalRepository::display_text_at(uint8_t col, uint8_t row, const char* message, bool clear_before) {
    const uint8_t safe_row = clamp_row(row);
    const uint8_t safe_col = clamp_col(col);
    const uint8_t cols = get_cols();

    if (clear_before) {
        clear_display();
    }

    if (cols == 0 || safe_col >= cols) {
        return;
    }

    set_cursor(safe_col, safe_row);
    print_trimmed(message, (uint8_t)(cols - safe_col));
}

void LiquidCrystalRepository::display_label_value_at(uint8_t col, uint8_t row, const char* label, float value, uint8_t precision, bool clear_before) {
    const uint8_t safe_row = clamp_row(row);
    const uint8_t safe_col = clamp_col(col);
    const uint8_t cols = get_cols();

    if (clear_before) {
        clear_display();
    }

    if (cols == 0 || safe_col >= cols) {
        return;
    }

    set_cursor(safe_col, safe_row);

    const uint8_t available_chars = (uint8_t)(cols - safe_col);
    uint8_t written = 0;

    if (label != nullptr) {
        for (uint8_t i = 0; label[i] != '\0' && written < available_chars; ++i, ++written) {
            print_raw(label[i]);
        }
    }

    if (written < available_chars) {
        print_raw(':');
        ++written;
    }

    if (written < available_chars) {
        print_raw(' ');
        ++written;
    }

    if (written < available_chars) {
        print_raw(value, precision);
    }
}

void LiquidCrystalRepository::display_two_rows(const char* first_row, const char* second_row, bool clear_before) {
    const char* rows[2] = { first_row, second_row };
    display_rows(rows, 2, clear_before);
}

void LiquidCrystalRepository::display_rows(const char* const* row_text_list, uint8_t row_count, bool clear_before) {
    const uint8_t rows = get_rows();

    if (clear_before) {
        clear_display();
    }

    for (uint8_t row = 0; row < rows; ++row) {
        const char* row_text = "";

        if (row_text_list != nullptr && row < row_count && row_text_list[row] != nullptr) {
            row_text = row_text_list[row];
        }

        render_row(row, row_text);
    }
}

void LiquidCrystalRepository::show_temporary_message(uint8_t col, uint8_t row, const char* message, unsigned long hold_ms, bool clear_before, bool clear_after) {
    display_text_at(col, row, message, clear_before);

    if (hold_ms > 0) {
        ::delay(hold_ms);
    }

    if (clear_after) {
        clear_display();
    }
}

void LiquidCrystalRepository::scroll_text_left(uint8_t row, const char* message, unsigned long step_delay_ms, bool clear_before) {
    const uint8_t safe_row = clamp_row(row);
    const uint8_t cols = get_cols();
    const size_t message_len = (message == nullptr) ? 0 : strlen(message);

    if (clear_before) {
        clear_display();
    }

    if (cols == 0) {
        return;
    }

    if (message_len <= cols) {
        render_row(safe_row, message == nullptr ? "" : message);
        return;
    }

    const size_t total_steps = message_len + cols;

    for (size_t step = 0; step < total_steps; ++step) {
        set_cursor(0, safe_row);

        for (uint8_t col_index = 0; col_index < cols; ++col_index) {
            const size_t window_index = step + col_index;
            char current_char = ' ';

            if (window_index >= cols) {
                const size_t message_index = window_index - cols;
                if (message_index < message_len) {
                    current_char = message[message_index];
                }
            }

            print_raw(current_char);
        }

        if (step_delay_ms > 0) {
            ::delay(step_delay_ms);
        }
    }
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
    lcd_ = new LiquidCrystal_I2C(lcd_addr_, en_, rw_, rs_, d4_, d5_, d6_, d7_, backlight_pin_, (t_backlighPol)backlight_polarity_);
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

void LiquidCrystalRepository::clear_display() {
    lcd_->clear();
}

void LiquidCrystalRepository::set_cursor(uint8_t col, uint8_t row) {
    lcd_->setCursor(col, row);
}

void LiquidCrystalRepository::print_raw(const char* data) {
    lcd_->print(data);
}

void LiquidCrystalRepository::print_raw(char data) {
    lcd_->print(data);
}

void LiquidCrystalRepository::print_raw(int32_t data) {
    lcd_->print((long)data);
}

void LiquidCrystalRepository::print_raw(uint8_t data) {
    lcd_->print(data);
}

void LiquidCrystalRepository::print_raw(float data, uint8_t precision) {
    lcd_->print(data, precision);
}

void LiquidCrystalRepository::backlight_on() {
    lcd_->backlight();
}

void LiquidCrystalRepository::backlight_off() {
    lcd_->noBacklight();
}

uint8_t LiquidCrystalRepository::clamp_row(uint8_t row) {
    const uint8_t rows = get_rows();

    if (rows == 0) {
        return 0;
    }

    if (row >= rows) {
        return (uint8_t)(rows - 1);
    }

    return row;
}

uint8_t LiquidCrystalRepository::clamp_col(uint8_t col) {
    const uint8_t cols = get_cols();

    if (cols == 0) {
        return 0;
    }

    if (col >= cols) {
        return (uint8_t)(cols - 1);
    }

    return col;
}

void LiquidCrystalRepository::print_trimmed(const char* message, uint8_t max_chars) {
    if (message == nullptr || max_chars == 0) {
        return;
    }

    for (uint8_t i = 0; message[i] != '\0' && i < max_chars; ++i) {
        print_raw(message[i]);
    }
}

void LiquidCrystalRepository::render_row(uint8_t row, const char* message) {
    const uint8_t cols = get_cols();

    set_cursor(0, clamp_row(row));

    uint8_t printed_chars = 0;

    if (message != nullptr) {
        for (; message[printed_chars] != '\0' && printed_chars < cols; ++printed_chars) {
            print_raw(message[printed_chars]);
        }
    }

    for (; printed_chars < cols; ++printed_chars) {
        print_raw(' ');
    }
}