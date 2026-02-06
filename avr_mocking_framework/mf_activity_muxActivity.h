#pragma once
#include <stdint.h>
#include <mf_repository_AvrMicroRepository.h>
class MultiplexerActivity {
public:
    MultiplexerActivity(AvrMicroRepository& avrMicroRepository,uint8_t pin_mux_0,uint8_t pin_mux_1,uint8_t pin_mux_2,uint8_t pin_mux_3);
    ~MultiplexerActivity();
    void set_multiplexer(int selected_channel);
    private:
    AvrMicroRepository* avrMicroRepository = nullptr;
    uint8_t pin_mux_0;
    uint8_t pin_mux_1 = 0;
    uint8_t pin_mux_2 = 0;
    uint8_t pin_mux_3 = 0;
};

