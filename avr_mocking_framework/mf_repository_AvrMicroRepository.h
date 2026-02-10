#pragma once
#include <stdint.h>
#include <mf_repository_ISerial.h>
#include <mf_commons_commonsLayer.h>
class AvrMicroRepository {
public:
    AvrMicroRepository(ISerial& serial, mf::commons::commonsLayer::AnalogRefMode vref_mode, float vref);
    // --- Funzioni analogiche ---
    virtual void analogReference(uint8_t mode);
    virtual uint16_t analogRead(uint8_t analogPin);
    virtual float analogVoltageRead(uint8_t analogPin);
    // --- Funzioni digitali ---
    virtual uint8_t digitalRead(uint8_t pin);
    virtual void digitalWrite(uint8_t pin, uint8_t value);
    virtual void pinMode(uint8_t pin, uint8_t mode);
    // --- Timing e memoria ---
    virtual void delay(unsigned long delayTime);
    virtual int getFreeRam();
    virtual void free(void* ptr);
    // --- Suoni ---
    //virtual void tone(unsigned int pin, unsigned int frequency, unsigned long duration = 0UL);
    //virtual void noTone(uint8_t pin);
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
    //virtual void print(int data, bool isNewLine = false);
    virtual int available();
    virtual size_t readString(char* buffer, size_t maxLen);
    virtual void clearBuffer();
    virtual int getSerialBufferSize();
    virtual void begin(unsigned long baud);
    virtual int read();
    // --- Software Serial control (ma senza tipi Arduino visibili) ---
    virtual ~AvrMicroRepository();
    virtual  unsigned long get_millis();
    virtual float get_vref();
private:
    ISerial& serial_;
    mf::commons::commonsLayer::AnalogRefMode vref_mode = mf::commons::commonsLayer::AnalogRefMode::DEFAULT_m;
    float vref = 0;
};
