
#include <mf_activity_muxActivity.h>
MultiplexerActivity::MultiplexerActivity(AvrMicroRepository& avrMicroRepository,DigitalPort** digitalPort, uint8_t digitalPortsNumber) : DigitalPortActivity(avrMicroRepository,digitalPort, digitalPortsNumber){
	this->pin_mux_0 = digitalPort[0]->get_pin();
	this->pin_mux_1 = digitalPort[1]->get_pin();
	this->pin_mux_2 = digitalPort[2]->get_pin();
	this->pin_mux_3 = digitalPort[3]->get_pin();
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
		this->digital_write(controlPin[i - 1],muxChannel[selected_channel][i- 1]);
            // cout << "control pin : " << (int)controlPin[i - 1];
            // cout << " channel : " << (int)muxChannel[selected_channel][i- 1]  << "\n";
	}
}

