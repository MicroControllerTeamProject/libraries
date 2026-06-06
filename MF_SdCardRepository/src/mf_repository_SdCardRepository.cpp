// File: mf_repository_SdCardRepository.cpp

#include "mf_repository_SdCardRepository.h"
#include <SD.h>
#include <SPI.h>
#include <string.h>
#ifdef _DEBUG_FOR_SERIAL
#include <Arduino.h>
#endif // _DEBUG_FOR_SERIAL

SdCardRepository::SdCardRepository(){
}

SdCardRepository::~SdCardRepository() {
}

bool SdCardRepository::begin(uint8_t chip_select_pin) {
    chip_select_pin_ = chip_select_pin;

    has_selected_file_ = false;
    selected_file_name_[0] = '\0';

    is_ready_ = SD.begin(chip_select_pin_);
    return is_ready_;
}

bool SdCardRepository::select_file(const char* file_name) {
    if (!is_ready_) {
        return false;
    }

    return copy_file_name(file_name);
}

bool SdCardRepository::append_text_line(const char* text_line) {
    if (!is_ready_ || !has_selected_file_ || text_line == 0) {
        return false;
    }

    File file = SD.open(selected_file_name_, FILE_WRITE);
    if (!file) {
        return false;
    }

    size_t written_bytes = file.println(text_line);
    file.close();

    return written_bytes > 0;
}

bool SdCardRepository::file_exists(const char* file_name) {
    if (!is_ready_ || file_name == 0 || file_name[0] == '\0') {
        return false;
    }

    return SD.exists(file_name);
}

// File: mf_repository_SdCardRepository.cpp
bool SdCardRepository::remove_file(const char* file_name) {
    if (!is_ready_ || file_name == 0 || file_name[0] == '\0') {
        return false;
    }

    bool removed = SD.remove(file_name);

    if (removed && has_selected_file_ && strcmp(selected_file_name_, file_name) == 0) {
        has_selected_file_ = false;
        selected_file_name_[0] = '\0';
    }

    return removed;
}

void SdCardRepository::close() {
    has_selected_file_ = false;
    selected_file_name_[0] = '\0';
}

bool SdCardRepository::is_ready() const {
    return is_ready_;
}

bool SdCardRepository::has_selected_file() const {
    return has_selected_file_;
}

bool SdCardRepository::copy_file_name(const char* source_file_name) {
    if (source_file_name == 0 || source_file_name[0] == '\0') {
        has_selected_file_ = false;
        selected_file_name_[0] = '\0';
        return false;
    }

    size_t file_name_length = strlen(source_file_name);
    if (file_name_length >= max_file_name_length) {
        has_selected_file_ = false;
        selected_file_name_[0] = '\0';
        return false;
    }

    memcpy(selected_file_name_, source_file_name, file_name_length);
    selected_file_name_[file_name_length] = '\0';
    has_selected_file_ = true;
    return true;
}