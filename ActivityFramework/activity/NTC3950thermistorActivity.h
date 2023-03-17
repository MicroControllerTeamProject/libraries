#pragma once
#include "DeviceActivity.h"
#include <math.h>

class NTC3950thermistorActivity : public DeviceActivity
{
public:
    NTC3950thermistorActivity(AnalogPort** analogPort, float vref, commonsLayer::analogRefMode mode, uint8_t analogPortsNumber, float r1_voltageResistor);
    bool isThereAnyPortsOnAlarm(AvrMicroRepository& avrMicroRepository);
  /*  float getTemperature();*/

private:
    float R_1;
    // fit coefficients
    float a = 283786.2;
    float b = 0.06593;
    float c = 49886.0;
    int avg_size = 10; // averaging size
};

