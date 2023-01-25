#pragma once
#include"..\repository\AvrMicroRepository.h"

class DigitalPort
{
public:
    enum AlarmOn : uint8_t
    {
        low,
        high
    };
    enum PortDirection : uint8_t
    {
        input,
        output
    };
    DigitalPort(char* uid, uint8_t pin);
    bool isEnable = true;
    bool	isOnError = false;
    PortDirection direction = PortDirection::output;
    /// <summary>
    /// Set low for trigger alarm on low level or high.
    /// </summary>
    AlarmOn alarmTriggerOn = AlarmOn::low;
    bool isOnPullUp = false;
    float minCustomMisureValue = 0.00f;
    float maxCustomMisureValue = 0.00f;
    /*String customMisureValueDescription = "";*/
    char* getUid();
    uint8_t getPin();
private:
    char* _uid;
    uint8_t _pin;
};

