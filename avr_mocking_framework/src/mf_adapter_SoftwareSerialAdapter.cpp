// mf_adapter_SoftwareSerialAdapter.cpp
#include <mf_adapter_SoftwareSerialAdapter.h>

SoftwareSerialAdapter::SoftwareSerialAdapter(SoftwareSerial& sw) noexcept
    : sw_(sw) {
}

void SoftwareSerialAdapter::begin(unsigned long baud) {
    sw_.begin(baud);
}

size_t SoftwareSerialAdapter::write(uint8_t byte) {
    return sw_.write(byte);
}

size_t SoftwareSerialAdapter::write(const uint8_t* buffer, size_t size) {
    return sw_.write(buffer, size);
}

size_t SoftwareSerialAdapter::write(const char* str) {
    return sw_.write(str);
}

size_t SoftwareSerialAdapter::write(const char* buffer, size_t size) {
    return sw_.write(buffer, size);
}

int SoftwareSerialAdapter::available() {
    return sw_.available();
}

int SoftwareSerialAdapter::read() {
    return sw_.read();
}

int SoftwareSerialAdapter::peek() {
    return sw_.peek();
}

void SoftwareSerialAdapter::flush() {
    sw_.flush();
}

size_t SoftwareSerialAdapter::readBytes(char* buffer, size_t length) {
    return sw_.readBytes(buffer, length);
}

size_t SoftwareSerialAdapter::readBytesUntil(char terminator, char* buffer, size_t length) {
    return sw_.readBytesUntil(terminator, buffer, length);
}

bool SoftwareSerialAdapter::find(const char* target) {
    return sw_.find(const_cast<char*>(target));
}

bool SoftwareSerialAdapter::findUntil(const char* target, char terminator) {
    char term_str[2] = { terminator, '\0' };
    return sw_.findUntil(const_cast<char*>(target), term_str);
}

long SoftwareSerialAdapter::parseInt() {
    return sw_.parseInt();
}

float SoftwareSerialAdapter::parseFloat() {
    return sw_.parseFloat();
}

void SoftwareSerialAdapter::setTimeout(unsigned long timeout) {
    sw_.setTimeout(timeout);
}

bool SoftwareSerialAdapter::listen() {
    return sw_.listen();
}

bool SoftwareSerialAdapter::isListening() {
    return sw_.isListening();
}

bool SoftwareSerialAdapter::stopListening() {
    return sw_.stopListening();
}

bool SoftwareSerialAdapter::is_listening() {
    return isListening();
}

bool SoftwareSerialAdapter::stop_listening() {
    return stopListening();
}

const int SoftwareSerialAdapter::getRxBufferSize() {
    return _SS_MAX_RX_BUFF;
}
