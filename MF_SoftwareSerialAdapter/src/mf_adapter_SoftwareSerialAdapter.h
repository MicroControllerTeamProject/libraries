// mf_adapter_SoftwareSerialAdapter.h
#pragma once

#include <mf_repository_ISerial.h>
#include <SoftwareSerial.h>

/// SoftwareSerialAdapter: adapter che fa da ponte tra SoftwareSerial di Arduino e l'interfaccia ISerial.
class SoftwareSerialAdapter : public ISerial {
public:
    explicit SoftwareSerialAdapter(SoftwareSerial& sw) noexcept;

    void begin(unsigned long baud) override;

    size_t write(uint8_t byte) override;
    size_t write(const uint8_t* buffer, size_t size) override;
    size_t write(const char* str) override;
    size_t write(const char* buffer, size_t size) override;

    int available() override;
    int read() override;
    int peek() override;
    void flush() override;

    size_t readBytes(char* buffer, size_t length) override;
    size_t readBytesUntil(char terminator, char* buffer, size_t length) override;

    bool find(const char* target) override;
    bool findUntil(const char* target, char terminator) override;

    long parseInt() override;
    float parseFloat() override;
    void setTimeout(unsigned long timeout) override;

    bool listen() override;
    bool isListening() override;
    bool stopListening() override;
    bool is_listening() override;
    bool stop_listening() override;

    const int getRxBufferSize() override;

private:
    SoftwareSerial& sw_;
};
