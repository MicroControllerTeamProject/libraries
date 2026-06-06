#pragma once
#include <stdint.h>
#include <mf_repository_ISerial.h>
#include <mf_commons_commonsLayer.h>

class AvrMicroRepository {
public:
    AvrMicroRepository(ISerial& serial, mf::commons::commonsLayer::AnalogRefMode vref_mode, float vref);
#if _ON_MOCKING_TESTS
    // --- Funzioni analogiche ---
    virtual void analogReference(uint8_t mode);
    virtual uint16_t analogRead(uint8_t analogPin);
    virtual float analogVoltageRead(uint8_t analogPin);
    // --- Funzioni digitali ---
    virtual uint8_t digitalRead(uint8_t pin);
    virtual void digitalWrite(uint8_t pin, uint8_t value);
    virtual void pinMode(uint8_t pin, uint8_t mode);
    // --- Stato configurazione pin ---
    virtual bool isPinOutput(uint8_t pin);
    virtual bool isPinInput(uint8_t pin);
    virtual bool isPinInputPullup(uint8_t pin);
    // --- Timing e memoria ---
    virtual void delay(unsigned long delayTime);
    virtual void delayMicroseconds(unsigned int micSec);
    virtual int getFreeRam();
    virtual void free(void* ptr);
    // --- Seriale: stampa e lettura ---
    virtual void print(const char* data);
    virtual void print(float data);
    virtual void print(int32_t data);
    virtual void print(uint8_t data);
    virtual void print(char data);
    virtual void println(const char* data);
    virtual void println(float data);
    virtual void println(int32_t data);
    virtual void println(uint8_t data);
    virtual void println(char data);
    virtual int available();
    virtual size_t readString(char* buffer, size_t maxLen);
    virtual void clearBuffer();
    virtual int getSerialBufferSize();
    virtual void begin(unsigned long baud);
    virtual int read();
    virtual ~AvrMicroRepository();
    virtual unsigned long get_millis();
    virtual unsigned long pulseIn(uint8_t pin, uint8_t level, unsigned long time = 1000000UL);
    virtual float get_vref();
#else
    // --- Funzioni analogiche ---
    void analogReference(uint8_t mode);
    uint16_t analogRead(uint8_t analogPin);
    float analogVoltageRead(uint8_t analogPin);
    // --- Funzioni digitali ---
    uint8_t digitalRead(uint8_t pin);
    void digitalWrite(uint8_t pin, uint8_t value);
    void pinMode(uint8_t pin, uint8_t mode);
    // --- Stato configurazione pin ---
    bool isPinOutput(uint8_t pin);
    bool isPinInput(uint8_t pin);
    bool isPinInputPullup(uint8_t pin);
    // --- Timing e memoria ---
    void delay(unsigned long delayTime);
    void delayMicroseconds(unsigned int micSec);
    int getFreeRam();
    void free(void* ptr);
    // --- Seriale: stampa e lettura ---
    void print(const char* data);
    void print(float data);
    void print(int32_t data);
    void print(uint8_t data);
    void print(char data);
    void println(const char* data);
    void println(float data);
    void println(int32_t data);
    void println(uint8_t data);
    void println(char data);
    int available();
    size_t readString(char* buffer, size_t maxLen);
    void clearBuffer();
    int getSerialBufferSize();
    void begin(unsigned long baud);
    int read();
    ~AvrMicroRepository();
    unsigned long get_millis();
    unsigned long pulseIn(uint8_t pin, uint8_t level, unsigned long time = 1000000UL);
    float get_vref();
#endif
private:
    ISerial& serial_;
    mf::commons::commonsLayer::AnalogRefMode vref_mode = mf::commons::commonsLayer::AnalogRefMode::DEFAULT_m;
    float vref = 0;
};
