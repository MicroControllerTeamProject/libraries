// HardwareSerialAdapter.h
#pragma once

#include <mf_repository_ISerial.h>
#include <HardwareSerial.h>

/// HardwareSerialAdapter: adapter che fa da ponte tra HardwareSerial di Arduino e l'interfaccia eSerial
class HardwareSerialAdapter : public ISerial {
public:
    /// Costruisce l'adapter su una porta HardwareSerial (es. Serial, Serial1, ...)
    explicit HardwareSerialAdapter(HardwareSerial& hw = Serial) noexcept
        : hw_(hw) {
    }
    /// Inizializza la seriale a baud
    void begin(unsigned long baud) override {
        hw_.begin(baud);
    }
    /// Write overloads
    size_t write(uint8_t byte) override {
        return hw_.write(byte);
    }
    size_t write(const uint8_t* buffer, size_t size) override {
        return hw_.write(buffer, size);
    }
    size_t write(const char* str) override {
        return hw_.write(str);
    }
    size_t write(const char* buffer, size_t size) override {
        return hw_.write(buffer, size);
    }
    /// Lettura/controllo disponibilità
    int available() override {
        return hw_.available();
    }
    int read() override {
        return hw_.read();
    }
    int peek() override {
        return hw_.peek();
    }
    void flush() override {
        hw_.flush();
    }
    /// Lettura con buffer
    size_t readBytes(char* buffer, size_t length) override {
        return hw_.readBytes(buffer, length);
    }
    size_t readBytesUntil(char terminator, char* buffer, size_t length) override {
        return hw_.readBytesUntil(terminator, buffer, length);
    }
    /// Ricerca e parsing
    /// Fix for the error: E0304  
    /// Update the `find` method in `HardwareSerialAdapter` to match the correct signature of `HardwareSerial::find`.  
    bool find(const char* target) override {  
        return hw_.find(const_cast<char*>(target));
    }
    bool findUntil(const char* target, char terminator) override {
        char termStr[2] = { terminator, '\0' };
        return hw_.findUntil(
            const_cast<char*>(target),
            termStr
        );
    }
    long parseInt() override {
        return hw_.parseInt();
    }
    float parseFloat() override {
        return hw_.parseFloat();
    }
    void setTimeout(unsigned long timeout) override {
        hw_.setTimeout(timeout);
    }
    /// Dimensione del buffer RX
    const int getRxBufferSize() override {
        return SERIAL_RX_BUFFER_SIZE;
    }
private:
    HardwareSerial& hw_;
};

