
#include <mf_activity_muxActivity.h>
MultiplexerActivity::MultiplexerActivity(AvrMicroRepository& avrMicroRepository,uint8_t pin_mux_0,uint8_t pin_mux_1,uint8_t pin_mux_2,uint8_t pin_mux_3){
	this->pin_mux_0 = pin_mux_0;
	this->pin_mux_1 = pin_mux_1;
	this->pin_mux_2 = pin_mux_2;
	this->pin_mux_3 = pin_mux_3;
	this->avrMicroRepository = &avrMicroRepository;
}
MultiplexerActivity::~MultiplexerActivity() {}
void MultiplexerActivity::set_multiplexer(int selected_channel) {
	uint8_t controlPin[4] = { this->pin_mux_3, this->pin_mux_2, this->pin_mux_1, this->pin_mux_0 };
	const uint8_t muxChannel[16][4] = {
		{0, 0, 0, 0}, // channel 0
		{1, 0, 0, 0}, // channel 1
		{0, 1, 0, 0}, // channel 2
		{1, 1, 0, 0}, // channel 3
		{0, 0, 1, 0}, // channel 4
		{1, 0, 1, 0}, // channel 5
		{0, 1, 1, 0}, // channel 6
		{1, 1, 1, 0}, // channel 7
		{0, 0, 0, 1}, // channel 8
		{1, 0, 0, 1}, // channel 9
		{0, 1, 0, 1}, // channel 10
		{1, 1, 0, 1}, // channel 11
		{0, 0, 1, 1}, // channel 12
		{1, 0, 1, 1}, // channel 13
		{0, 1, 1, 1}, // channel 14
		{1, 1, 1, 1}  // channel 15
	};
	for (int i = 4; i > 0; i--) {
		this->avrMicroRepository->digitalWrite(controlPin[i - 1],muxChannel[selected_channel][i- 1]);
            // cout << "control pin : " << (int)controlPin[i - 1];
            // cout << " channel : " << (int)muxChannel[selected_channel][i- 1]  << "\n";

	}
}

