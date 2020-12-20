#include "VoltageActivity.h"

VoltageActivity::VoltageActivity(AnalogPort** analogPort, float vref, uint8_t digitalPortsNumber) : DeviceActivity(analogPort, vref, digitalPortsNumber) {
}