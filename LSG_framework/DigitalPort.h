#pragma once
#include <arduino.h>
#include <pins_arduino.h>
#include "Commons.h"


//enum Direction
//{
//    input,
//    output
//};

class DigitalPort
{
    
public:
    enum AlarmOn
    {
        low,
        high
    };

    String uid;
    bool isEnable = true;
    uint8_t pin;
    PortDirection direction = output;
    AlarmOn alarmOn = low;
    bool isOnPullUp = false;
    float unitOfMisureFullScale = 0;
    float maxUnitOfMisureAlarmValue = 0;
    float minUnitOfMisureAlarmValue = 0;
};

