// mf_adapter_HardwareSerialAdapter.h
#pragma once

#include <mf_repository_ISerial.h>
#include <HardwareSerial.h>

/// HardwareSerialAdapter: adapter che fa da ponte tra HardwareSerial di Arduino e l'interfaccia ISerial.
class HardwareSerialAdapter : public ISerial {
public:
    /// Costruisce l'adapter su una porta HardwareSerial (es. Serial, Serial1, ...).
    explicit HardwareSerialAdapter(HardwareSerial& hw = Serial) noexcept;

    /// Inizializza la seriale a baud.
    void begin(unsigned long baud) override;

    /// Write overloads.
    size_t write(uint8_t byte) override;
    size_t write(const uint8_t* buffer, size_t size) override;
    size_t write(const char* str) override;
    size_t write(const char* buffer, size_t size) override;

    /// Lettura/controllo disponibilita'.
    int available() override;
    int read() override;
    int peek() override;
    void flush() override;

    /// Lettura con buffer.
    size_t readBytes(char* buffer, size_t length) override;
    size_t readBytesUntil(char terminator, char* buffer, size_t length) override;

    /// Ricerca e parsing.
    bool find(const char* target) override;
    bool findUntil(const char* target, char terminator) override;
    long parseInt() override;
    float parseFloat() override;
    void setTimeout(unsigned long timeout) override;

    /// HardwareSerial non richiede listen(): questi metodi sono no-op espliciti.
    bool listen() override;
    bool isListening() override;
    bool stopListening() override;
    bool is_listening() override;
    bool stop_listening() override;

    /// Dimensione del buffer RX.
    const int getRxBufferSize() override;

private:
    HardwareSerial& hw_;
};
