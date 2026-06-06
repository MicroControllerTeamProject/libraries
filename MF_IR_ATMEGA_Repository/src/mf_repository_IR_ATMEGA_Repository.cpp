
#include <mf_repository_IR_ATMEGA_Repository.h>
#include <IRremote.h> // use the library
IRsend irsend;
IRrecv irrecv(11);
decode_results results;
IR_ATMEGA_Repository::IR_ATMEGA_Repository(uint8_t rx_pin) {
	this->pin_receiver = rx_pin;
	init();
}
IR_ATMEGA_Repository::~IR_ATMEGA_Repository() {
}
bool IR_ATMEGA_Repository::init() {
	//IRrecv irrecv(this->pin_receiver); // create instance of 'irrecv'
	irrecv.enableIRIn(); // Start the receiver
}
bool IR_ATMEGA_Repository::is_available() {
	return irrecv.decode(&results);
}
bool IR_ATMEGA_Repository::check_received_code(unsigned long code_to_find) {
	if (results.value == code_to_find) return true;
	return false;
}
void IR_ATMEGA_Repository::resume() {
	irrecv.resume();
}
void IR_ATMEGA_Repository::send(unsigned long code, int nbits) {
	irsend.sendNEC(code, nbits);
}
void IR_ATMEGA_Repository::enable_to_receive() {
	irrecv.enableIRIn(); // Start the receiver
}





