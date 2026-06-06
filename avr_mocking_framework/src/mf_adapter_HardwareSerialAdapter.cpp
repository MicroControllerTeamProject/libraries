// mf_adapter_HardwareSerialAdapter.cpp
#include <mf_adapter_HardwareSerialAdapter.h>

HardwareSerialAdapter::HardwareSerialAdapter(HardwareSerial& hw) noexcept
    : hw_(hw) {
}

void HardwareSerialAdapter::begin(unsigned long baud) {
    hw_.begin(baud);
}

size_t HardwareSerialAdapter::write(uint8_t byte) {
    return hw_.write(byte);
}

size_t HardwareSerialAdapter::write(const uint8_t* buffer, size_t size) {
    return hw_.write(buffer, size);
}

size_t HardwareSerialAdapter::write(const char* str) {
    return hw_.write(str);
}

size_t HardwareSerialAdapter::write(const char* buffer, size_t size) {
    return hw_.write(buffer, size);
}

int HardwareSerialAdapter::available() {
    return hw_.available();
}

int HardwareSerialAdapter::read() {
    return hw_.read();
}

int HardwareSerialAdapter::peek() {
    return hw_.peek();
}

void HardwareSerialAdapter::flush() {
    hw_.flush();
}

size_t HardwareSerialAdapter::readBytes(char* buffer, size_t length) {
    return hw_.readBytes(buffer, length);
}

size_t HardwareSerialAdapter::readBytesUntil(char terminator, char* buffer, size_t length) {
    return hw_.readBytesUntil(terminator, buffer, length);
}

bool HardwareSerialAdapter::find(const char* target) {
    return hw_.find(const_cast<char*>(target));
}

bool HardwareSerialAdapter::findUntil(const char* target, char terminator) {
    char term_str[2] = { terminator, '\0' };
    return hw_.findUntil(const_cast<char*>(target), term_str);
}

long HardwareSerialAdapter::parseInt() {
    return hw_.parseInt();
}

float HardwareSerialAdapter::parseFloat() {
    return hw_.parseFloat();
}

void HardwareSerialAdapter::setTimeout(unsigned long timeout) {
    hw_.setTimeout(timeout);
}

bool HardwareSerialAdapter::listen() {
    return true;
}

bool HardwareSerialAdapter::isListening() {
    return true;
}

bool HardwareSerialAdapter::stopListening() {
    return true;
}

bool HardwareSerialAdapter::is_listening() {
    return isListening();
}

bool HardwareSerialAdapter::stop_listening() {
    return stopListening();
}

const int HardwareSerialAdapter::getRxBufferSize() {
    return SERIAL_RX_BUFFER_SIZE;
}
