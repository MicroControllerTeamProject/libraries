#pragma once
#include <C:\Program Files (x86)\arduino-1.8.5\hardware\arduino\avr\cores\arduino\Arduino.h>
#include <pins_arduino.h>
#include "Commons.h"

class DigitalPort
{
public:
    enum AlarmOn
    {
        low,
        high
    };

    DigitalPort(String uid, uint8_t pin, uint8_t mode);
    bool isEnable = true;
    uint8_t mode = OUTPUT;
    /*PortDirection direction = output;*/
    /// <summary>
    /// Set low for trigger alarm on low level or high.
    /// </summary>
    AlarmOn alarmOn = low;
  /*  bool isOnPullUp = false;*/
    float minCustomMisureValue = 0.00f;
    float maxCustomMisureValue = 0.00f;
    String customMisureValueDescription = "";
    String getUid();
    uint8_t getPin();
private:
    String _uid;
    uint8_t _pin;
};

