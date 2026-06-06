// File: mf_repository_SdCardRepository.h
#pragma once
#include <stdint.h>

class SdCardRepository {
public:
    SdCardRepository();
    virtual ~SdCardRepository();
    virtual bool begin(uint8_t chip_select_pin);
    virtual bool select_file(const char* file_name);
    virtual bool append_text_line(const char* text_line);
    virtual bool file_exists(const char* file_name);
    virtual bool remove_file(const char* file_name);
    virtual void close();
    virtual bool is_ready() const;
    virtual bool has_selected_file() const;

private:
    static const uint8_t max_file_name_length = 32;

    uint8_t chip_select_pin_ = 0;
    bool is_ready_ = false;
    bool has_selected_file_ = false;
    char selected_file_name_[max_file_name_length] = {};

    bool copy_file_name(const char* source_file_name);
};
