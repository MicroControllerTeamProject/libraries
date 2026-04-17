#include <mf_activity_LiquidCrystalActivity.h>
#include <stdio.h>
#include <string.h>

LiquidCrystalActivity::LiquidCrystalActivity(LiquidCrystalRepository& liquid_crystal_repository,
    AvrMicroRepository& avrMicroRepository)
    : liquid_crystal_repository(liquid_crystal_repository)
    , avrMicroRepository(avrMicroRepository) {
    configure();
}

LiquidCrystalActivity::LiquidCrystalActivity(LiquidCrystalRepository& liquid_crystal_repository,
    AvrMicroRepository& avrMicroRepository,
    uint8_t cols,
    uint8_t rows,
    bool enable_backlight)
    : liquid_crystal_repository(liquid_crystal_repository)
    , avrMicroRepository(avrMicroRepository) {
    configure(cols, rows, enable_backlight, true);
}

LiquidCrystalActivity::LiquidCrystalActivity(LiquidCrystalRepository& liquid_crystal_repository,
    AvrMicroRepository& avrMicroRepository,
    uint8_t cols,
    uint8_t rows,
    bool enable_backlight,
    bool auto_configure)
    : liquid_crystal_repository(liquid_crystal_repository)
    , avrMicroRepository(avrMicroRepository) {
    if (auto_configure) {
        configure(cols, rows, enable_backlight, true);
    }
}

void LiquidCrystalActivity::configure(uint8_t cols, uint8_t rows, bool enable_backlight, bool clear_display) {
    if (cols == 0) cols = 16;
    if (rows == 0) rows = 2;

    liquid_crystal_repository.begin(cols, rows);

    if (enable_backlight) {
        liquid_crystal_repository.backlight_on();
    }
    else {
        liquid_crystal_repository.backlight_off();
    }

    if (clear_display) {
        liquid_crystal_repository.clear();
    }
}

uint8_t LiquidCrystalActivity::get_i2c_address() {
    return liquid_crystal_repository.get_i2c_address();
}

void LiquidCrystalActivity::clear() {
    liquid_crystal_repository.clear();
}

void LiquidCrystalActivity::print_at(uint8_t col, uint8_t row, const char* message, bool clear_before) {
    const uint8_t safe_row = clamp_row(row);
    const uint8_t safe_col = clamp_col(col);
    const uint8_t cols = liquid_crystal_repository.get_cols();

    if (clear_before) {
        liquid_crystal_repository.clear();
    }

    if (cols == 0 || safe_col >= cols) {
        return;
    }

    liquid_crystal_repository.set_cursor(safe_col, safe_row);
    print_trimmed(message, (uint8_t)(cols - safe_col));
}

void LiquidCrystalActivity::clear_and_print_at(uint8_t col, uint8_t row, const char* message) {
    print_at(col, row, message, true);
}

void LiquidCrystalActivity::print_labeled_value_at(uint8_t col,
    uint8_t row,
    const char* label,
    float value,
    uint8_t precision,
    bool clear_before) {
    const uint8_t safe_row = clamp_row(row);
    const uint8_t safe_col = clamp_col(col);
    const uint8_t cols = liquid_crystal_repository.get_cols();
    char value_buffer[24];

    if (clear_before) {
        liquid_crystal_repository.clear();
    }

    if (cols == 0 || safe_col >= cols) {
        return;
    }

    snprintf(value_buffer, sizeof(value_buffer), "%.*f", precision, value);

    liquid_crystal_repository.set_cursor(safe_col, safe_row);

    const uint8_t available_chars = (uint8_t)(cols - safe_col);
    uint8_t written = 0;

    if (label != nullptr) {
        for (uint8_t i = 0; label[i] != '\0' && written < available_chars; ++i, ++written) {
            liquid_crystal_repository.print(label[i]);
        }
    }

    if (written < available_chars) {
        liquid_crystal_repository.print(':');
        ++written;
    }

    if (written < available_chars) {
        liquid_crystal_repository.print(' ');
        ++written;
    }

    if (written < available_chars) {
        print_trimmed(value_buffer, (uint8_t)(available_chars - written));
    }
}

void LiquidCrystalActivity::render_two_rows(const char* first_row, const char* second_row, bool clear_before) {
    const char* rows[2] = { first_row, second_row };
    render_rows(rows, 2, clear_before);
}

void LiquidCrystalActivity::render_rows(const char* const* row_text_list, uint8_t row_count, bool clear_before) {
    const uint8_t rows = liquid_crystal_repository.get_rows();

    if (clear_before) {
        liquid_crystal_repository.clear();
    }

    for (uint8_t row = 0; row < rows; ++row) {
        const char* row_text = "";

        if (row_text_list != nullptr && row < row_count && row_text_list[row] != nullptr) {
            row_text = row_text_list[row];
        }

        render_row(row, row_text);
    }
}

void LiquidCrystalActivity::show_temporary_message(uint8_t col,
    uint8_t row,
    const char* message,
    unsigned long hold_ms,
    bool clear_before) {
    print_at(col, row, message, clear_before);

    if (hold_ms > 0) {
        avrMicroRepository.delay(hold_ms);
    }

    liquid_crystal_repository.clear();
}

void LiquidCrystalActivity::scroll_message_left(uint8_t row,
    const char* message,
    unsigned long step_delay_ms,
    bool clear_before) {
    const uint8_t safe_row = clamp_row(row);
    const uint8_t cols = liquid_crystal_repository.get_cols();
    const size_t message_len = (message == nullptr) ? 0 : strlen(message);

    if (clear_before) {
        liquid_crystal_repository.clear();
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
        liquid_crystal_repository.set_cursor(0, safe_row);

        for (uint8_t col_index = 0; col_index < cols; ++col_index) {
            const size_t window_index = step + col_index;
            char current_char = ' ';

            if (window_index >= cols) {
                const size_t message_index = window_index - cols;
                if (message_index < message_len) {
                    current_char = message[message_index];
                }
            }

            liquid_crystal_repository.print(current_char);
        }

        if (step_delay_ms > 0) {
            avrMicroRepository.delay(step_delay_ms);
        }
    }
}

uint8_t LiquidCrystalActivity::clamp_row(uint8_t row) {
    const uint8_t rows = liquid_crystal_repository.get_rows();

    if (rows == 0) {
        return 0;
    }

    if (row >= rows) {
        return (uint8_t)(rows - 1);
    }

    return row;
}

uint8_t LiquidCrystalActivity::clamp_col(uint8_t col) {
    const uint8_t cols = liquid_crystal_repository.get_cols();

    if (cols == 0) {
        return 0;
    }

    if (col >= cols) {
        return (uint8_t)(cols - 1);
    }

    return col;
}

void LiquidCrystalActivity::print_trimmed(const char* message, uint8_t max_chars) {
    if (message == nullptr || max_chars == 0) {
        return;
    }

    for (uint8_t i = 0; message[i] != '\0' && i < max_chars; ++i) {
        liquid_crystal_repository.print(message[i]);
    }
}

void LiquidCrystalActivity::render_row(uint8_t row, const char* message) {
    const uint8_t cols = liquid_crystal_repository.get_cols();

    liquid_crystal_repository.set_cursor(0, clamp_row(row));

    uint8_t printed_chars = 0;

    if (message != nullptr) {
        for (; message[printed_chars] != '\0' && printed_chars < cols; ++printed_chars) {
            liquid_crystal_repository.print(message[printed_chars]);
        }
    }

    for (; printed_chars < cols; ++printed_chars) {
        liquid_crystal_repository.print(' ');
    }
}
