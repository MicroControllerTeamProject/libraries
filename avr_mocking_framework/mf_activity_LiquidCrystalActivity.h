#pragma once
#include <stdint.h>
#include "mf_repository_AvrMicroRepository.h"
#include "mf_repository_LiquidCrystalRepository.h"

class LiquidCrystalActivity {
public:
    LiquidCrystalActivity(LiquidCrystalRepository& liquid_crystal_repository,
        AvrMicroRepository& avrMicroRepository);
    LiquidCrystalActivity(LiquidCrystalRepository& liquid_crystal_repository,
        AvrMicroRepository& avrMicroRepository,
        uint8_t cols,
        uint8_t rows,
        bool enable_backlight = true);
    LiquidCrystalActivity(LiquidCrystalRepository& liquid_crystal_repository,
        AvrMicroRepository& avrMicroRepository,
        uint8_t cols,
        uint8_t rows,
        bool enable_backlight,
        bool auto_configure);

    void configure(uint8_t cols = 16, uint8_t rows = 2, bool enable_backlight = true, bool clear_display = true);
    uint8_t get_i2c_address();
    void clear();
    void print_at(uint8_t col, uint8_t row, const char* message, bool clear_before = false);
    void clear_and_print_at(uint8_t col, uint8_t row, const char* message);
    void print_labeled_value_at(uint8_t col, uint8_t row, const char* label, float value, uint8_t precision = 2, bool clear_before = false);
    void render_two_rows(const char* first_row, const char* second_row, bool clear_before = true);
    void render_rows(const char* const* row_text_list, uint8_t row_count, bool clear_before = true);
    void show_temporary_message(uint8_t col, uint8_t row, const char* message, unsigned long hold_ms, bool clear_before = true);
    void scroll_message_left(uint8_t row, const char* message, unsigned long step_delay_ms = 250, bool clear_before = true);

private:
    LiquidCrystalRepository& liquid_crystal_repository;
    AvrMicroRepository& avrMicroRepository;

    uint8_t clamp_row(uint8_t row);
    uint8_t clamp_col(uint8_t col);
    void print_trimmed(const char* message, uint8_t max_chars);
    void render_row(uint8_t row, const char* message);
};
