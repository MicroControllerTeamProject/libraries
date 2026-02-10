// SoftwareSerialAdapter.h
#pragma once
#include <mf_repository_ISerial.h>
#include <SoftwareSerial.h>
/// SoftwareSerialAdapter: adapter che fa da ponte tra SoftwareSerial di Arduino e l'interfaccia ISerial
class SoftwareSerialAdapter : public ISerial {
public:
    /// Costruisce l'adapter su una porta SoftwareSerial
    explicit SoftwareSerialAdapter(SoftwareSerial& sw) noexcept
        : sw_(sw) {
    }
    /// Inizializza la seriale a baud
    void begin(unsigned long baud) override {
        sw_.begin(baud);
    }
    /// Write overloads
    size_t write(uint8_t byte) override {
        return sw_.write(byte);
    }
    size_t write(const uint8_t* buffer, size_t size) override {
        return sw_.write(buffer, size);
    }
    size_t write(const char* str) override {
        return sw_.write(str);
    }
    size_t write(const char* buffer, size_t size) override {
        return sw_.write(buffer, size);
    }
    /// Lettura/controllo disponibilità
    int available() override {
        return sw_.available();
    }
    int read() override {
        return sw_.read();
    }
    int peek() override {
        return sw_.peek();
    }
    void flush() override {
        sw_.flush();
    }
    /// Lettura con buffer
    size_t readBytes(char* buffer, size_t length) override {
        return sw_.readBytes(buffer, length);
    }
    size_t readBytesUntil(char terminator, char* buffer, size_t length) override {
        return sw_.readBytesUntil(terminator, buffer, length);
    }
    /// Ricerca e parsing
    bool find(const char* target) override {
        return sw_.find(const_cast<char*>(target));
    }
    bool findUntil(const char* target, char terminator) override {
        char termStr[2] = { terminator, '\0' };
        return sw_.findUntil(
            const_cast<char*>(target),
            termStr
        );
    }
    long parseInt() override {
        return sw_.parseInt();
    }
    float parseFloat() override {
        return sw_.parseFloat();
    }
    void setTimeout(unsigned long timeout) override {
        sw_.setTimeout(timeout);
    }
    /// Dimensione del buffer RX (SoftwareSerial usa internamente ~64 byte)
    const int getRxBufferSize() override {
        return _SS_MAX_RX_BUFF;
    }
private:
    SoftwareSerial& sw_;
};
