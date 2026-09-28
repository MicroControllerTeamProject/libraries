#pragma once
#include <stdint.h>
#include <mf_repository_AvrMicroRepository.h>
#include <mf_activity_DigitalPortActivity.h>
class MultiplexerActivity : public DigitalPortActivity {
public:
    MultiplexerActivity(AvrMicroRepository& avrMicroRepository, DigitalPort** digitalPort, uint8_t digitalPortsNumber);
    ~MultiplexerActivity();
    void set_multiplexer(int selected_channel);
    private:
    AvrMicroRepository* avrMicroRepository = nullptr;
    uint8_t pin_mux_0 = 0;
    uint8_t pin_mux_1 = 0;
    uint8_t pin_mux_2 = 0;
    uint8_t pin_mux_3 = 0;
};

