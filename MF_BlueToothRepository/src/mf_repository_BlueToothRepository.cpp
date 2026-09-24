#include <mf_repository_BlueToothRepository.h>
#include <Arduino.h>
#include <stdlib.h>
#include <string.h>

#define ATPASSW_Q "AT+PSWD?"
#define ATPASSW_R "AT+PSWD="
#define ATNAME_Q "AT+NAME?"
#define ATNAME_R "AT+NAME="
#define ATRNAME_Q "AT+RNAME?"
#define ATROLE0 "AT+ROLE=0"
#define ATROLE1 "AT+ROLE=1"
#define ATCMODE0 "AT+CMODE=0"
#define ATUART9600 "AT+UART=9600,0,0"
#define ATVERSION_Q "AT+VERSION?"

//#define LITERAL_RETURN "\r\n"
//#define LITERAL_OK "OK"

#define OUTPUT 1
#define INPUT 0

BlueToothRepository::BlueToothRepository(
	AvrMicroRepository& avrMicroRepository,
	uint8_t blueToothKeyPin,
	unsigned long baudRateProgramMode,
	unsigned long baudRateReceveMode)
	: BlueToothRepository(
		avrMicroRepository,
		blueToothKeyPin,
		255,
		baudRateProgramMode,
		baudRateReceveMode) {
}

BlueToothRepository::BlueToothRepository(
	AvrMicroRepository& avrMicroRepository,
	uint8_t blueToothKeyPin,
	uint8_t baseTransistorPin,
	unsigned long baudRateProgramMode,
	unsigned long baudRateReceveMode) {

	this->baseTransistorPin = baseTransistorPin;
	this->avrMicroRepository = &avrMicroRepository;
	this->blueToothKeyPin = blueToothKeyPin;
	this->baudRateProgramMode = baudRateProgramMode;
	this->baudRateReceveMode = baudRateReceveMode;

	this->avrMicroRepository->pinMode(
		this->blueToothKeyPin,
		OUTPUT);

	if (this->baseTransistorPin != 255) {
		this->avrMicroRepository->pinMode(
			this->baseTransistorPin,
			OUTPUT);
	}
}

BlueToothRepository::~BlueToothRepository() {
}
bool BlueToothRepository::is_device_detected(const char* bt_address, const char* device_name) {
	this->avrMicroRepository->clearBuffer();
	const char* response_prefix = "+RNAME:";
	const char* expected_name = device_name != nullptr ? device_name : "";
	const char* next_expected_char = response_prefix;
	bool is_matching_name = false;
	unsigned long start_time = this->avrMicroRepository->get_millis();
	unsigned long last_query_time = start_time;
	bool is_first_query = true;
	while (true) {
		unsigned long current_time = this->avrMicroRepository->get_millis();
		if (current_time - start_time >= 30000UL) {
			break;
		}
		if (!this->avrMicroRepository->available()) {
			if (is_first_query || current_time - last_query_time >= 5000UL) {
				this->avrMicroRepository->print(ATRNAME_Q);
				this->avrMicroRepository->print(bt_address);
				this->avrMicroRepository->print(LITERAL_RETURN);
				last_query_time = current_time;
				is_first_query = false;
				next_expected_char = response_prefix;
				is_matching_name = false;
			}
			continue;
		}
		const char current_char = this->avrMicroRepository->read();
		if (current_char == '\r' || current_char == '\n') {
			if (is_matching_name && expected_name[0] != '\0' && next_expected_char != nullptr && *next_expected_char == '\0') {
#if _DEBUG_FOR_SERIAL && !_ON_MOCKING_TESTS
				Serial.print(F("BT detected: +RNAME:"));
				Serial.println(device_name);
#endif
				return true;
			}
			next_expected_char = response_prefix;
			is_matching_name = false;
			continue;
		}
		if (next_expected_char == nullptr) {
			continue;
		}
		if (*next_expected_char == '\0' || current_char != *next_expected_char) {
			next_expected_char = nullptr;
			continue;
		}
		++next_expected_char;
		if (!is_matching_name && *next_expected_char == '\0') {
			next_expected_char = expected_name;
			is_matching_name = true;
		}
	}
	return false;
}
void BlueToothRepository::set_to_master_mode() {
	if (!is_in_program_mode) {
		set_to_program_mode();
	}
	this->avrMicroRepository->println(ATROLE1);
	SerialUtils::wait_for_pattern(
		*this->avrMicroRepository,
		LITERAL_OK,
		2000);

	this->avrMicroRepository->println(ATCMODE0);

	SerialUtils::wait_for_pattern(
		*this->avrMicroRepository,
		LITERAL_OK,
		2000);

	is_in_master_mode = true;
	is_in_slave_mode = false;
	is_in_program_mode = true;
	is_in_receive_mode = false;

#if _DEBUG_FOR_SERIAL && !_ON_MOCKING_TESTS
	Serial.println(F("BT master mode"));
#endif
}
void BlueToothRepository::find_mode_v3() {
	if (baseTransistorPin == 255) {
		return;
	}
	this->avrMicroRepository->digitalWrite(this->baseTransistorPin, LOW);
	this->avrMicroRepository->delay(2000);
	this->avrMicroRepository->digitalWrite(this->baseTransistorPin, HIGH);
	this->avrMicroRepository->delay(3000);
	this->avrMicroRepository->digitalWrite(this->blueToothKeyPin, HIGH);
	this->avrMicroRepository->begin(this->baudRateReceveMode);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 2000);
	is_in_receive_mode = true;
}
void BlueToothRepository::set_to_program_mode() {
	if (is_in_program_mode) {
		return;
	}
	this->avrMicroRepository->digitalWrite(this->blueToothKeyPin, HIGH);
	if (baseTransistorPin != 255) {
		this->avrMicroRepository->digitalWrite(this->baseTransistorPin, LOW);
	}
	this->avrMicroRepository->delay(100);
	if (baseTransistorPin != 255) {
		this->avrMicroRepository->digitalWrite(this->baseTransistorPin, HIGH);
	}
	this->avrMicroRepository->delay(200);
	this->avrMicroRepository->begin(
		this->baudRateProgramMode);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 2000);
	is_in_program_mode = true;
	is_in_slave_mode = false;
#if _DEBUG_FOR_SERIAL && !_ON_MOCKING_TESTS
	Serial.println(F("BT program mode"));
#endif
}
void BlueToothRepository::set_to_receive_mode() {
	if (!is_in_slave_mode) {
		return;
	}
	this->avrMicroRepository->digitalWrite(this->blueToothKeyPin, LOW);
	if (baseTransistorPin != 255) {
		this->avrMicroRepository->digitalWrite(this->baseTransistorPin, LOW);
	}
	this->avrMicroRepository->delay(100);
	if (baseTransistorPin != 255) {
		this->avrMicroRepository->digitalWrite(this->baseTransistorPin, HIGH);
	}
	this->avrMicroRepository->delay(200);
	this->avrMicroRepository->begin(this->baudRateReceveMode);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 2000);
	is_in_receive_mode = true;
	is_in_program_mode = false;
}
void BlueToothRepository::set_to_slave_mode() {
	if (is_in_slave_mode) {
		return;
	}
	if (!is_in_program_mode) {
		this->set_to_program_mode();
	}
	this->avrMicroRepository->println(ATROLE0);
	SerialUtils::wait_for_pattern(
		*this->avrMicroRepository,
		LITERAL_OK,
		1500);
	this->avrMicroRepository->println(ATUART9600);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 1500);
	is_in_slave_mode = true;
	is_in_master_mode = false;
	is_in_program_mode = false;
#if _DEBUG_FOR_SERIAL && !_ON_MOCKING_TESTS
	Serial.println(F("BT slave mode"));
#endif
	this->set_to_receive_mode();
}
void BlueToothRepository::turnOffBlueTooth() {
	if (baseTransistorPin == 255) {
		return;
	}

	this->avrMicroRepository->digitalWrite(
		this->baseTransistorPin,
		LOW);

	this->is_bluetooth_on = false;
}
void BlueToothRepository::turnOnBlueTooth() {

	if (baseTransistorPin == 255) {
		return;
	}

	this->avrMicroRepository->digitalWrite(
		this->baseTransistorPin,
		HIGH);

	this->is_bluetooth_on = true;
}
bool BlueToothRepository::isBluetoothOn() {

	return this->is_bluetooth_on;
}
void BlueToothRepository::get_version(char* version, uint8_t maxLength) {
	if (version == nullptr || maxLength == 0) {
		return;
	}
	if (!is_in_program_mode) {
		this->set_to_program_mode();
	}
	this->avrMicroRepository->clearBuffer();
	this->avrMicroRepository->println(ATVERSION_Q);
	uint8_t i = 0;

	unsigned long start =
		this->avrMicroRepository->get_millis();

	while (
		i < 3 &&
		i < maxLength - 1 &&
		(this->avrMicroRepository->get_millis() - start < 1000)) {

		if (this->avrMicroRepository->available()) {

			char c =
				this->avrMicroRepository->read();

			if ((c >= '0' && c <= '9') || c == '.') {
				version[i++] = c;
			}
		}
	}

	version[i] = '\0';
}
void BlueToothRepository::get_current_password(char* currentPassword, uint8_t maxLength) {
	if (currentPassword == nullptr || maxLength == 0) {
		return;
	}
	if (!is_in_program_mode) {
		this->set_to_program_mode();
	}
	this->avrMicroRepository->clearBuffer();
	this->avrMicroRepository->print(ATPASSW_Q);
	this->avrMicroRepository->print(LITERAL_RETURN);

	bool found_colon = false;

	uint8_t i = 0;

	unsigned long start =
		this->avrMicroRepository->get_millis();

	while (
		(this->avrMicroRepository->get_millis() - start) < 1000) {

		if (this->avrMicroRepository->available()) {

			char c =
				this->avrMicroRepository->read();

			if (found_colon) {

				if (
					i < 4 &&
					i < maxLength - 1 &&
					c >= '0' &&
					c <= '9') {

					currentPassword[i++] = c;
				}
				else if (i >= 4) {
					break;
				}
			}

			if (c == ':') {
				found_colon = true;
			}
		}
	}

	currentPassword[i] = '\0';
}
void BlueToothRepository::set_password(const char* pw) {
	if (!is_in_program_mode) {
		set_to_program_mode();
	}
	avrMicroRepository->clearBuffer();
	avrMicroRepository->print(ATPASSW_R);
	avrMicroRepository->print(pw);
	avrMicroRepository->print(LITERAL_RETURN);
	unsigned long start = avrMicroRepository->get_millis();
	bool ok = false;
	uint8_t state = 0;
	while (
		(avrMicroRepository->get_millis() - start) < 1000 && !ok) {
		if (avrMicroRepository->available()) {
			char c = avrMicroRepository->read();
			if (state == 0) {
				state = (c == 'O');
			}
			else {
				if (c == 'K') {
					ok = true;
				}
				else {
					state = (c == 'O');
				}
			}
		}
	}
	if (!ok) {
		// Timeout.
	}
}
void BlueToothRepository::set_name(const char* name) {
	if (!is_in_program_mode) {
		set_to_program_mode();
	}
	avrMicroRepository->clearBuffer();
	avrMicroRepository->print(ATNAME_R);
	avrMicroRepository->print(name);
	avrMicroRepository->print(LITERAL_RETURN);

	unsigned long start =
		avrMicroRepository->get_millis();

	bool ok = false;

	uint8_t state = 0;

	while (
		(avrMicroRepository->get_millis() - start) < 1000 &&
		!ok) {

		if (avrMicroRepository->available()) {

			char c =
				avrMicroRepository->read();

			if (state == 0) {

				state = (c == 'O');
			}
			else {

				if (c == 'K') {

					ok = true;
				}
				else {

					state = (c == 'O');
				}
			}
		}
	}

	if (!ok) {
		// Timeout.
	}
}


void BlueToothRepository::get_name(
	char* name,
	uint8_t maxLength) {

	if (name == nullptr || maxLength == 0) {
		return;
	}

	if (!is_in_program_mode) {
		this->set_to_program_mode();
	}

	this->avrMicroRepository->clearBuffer();

	this->avrMicroRepository->print(ATNAME_Q);
	this->avrMicroRepository->print(LITERAL_RETURN);

	bool found_colon = false;

	uint8_t i = 0;

	unsigned long start =
		this->avrMicroRepository->get_millis();

	while (
		(this->avrMicroRepository->get_millis() - start) < 1000) {

		if (this->avrMicroRepository->available()) {

			char c =
				this->avrMicroRepository->read();

			if (found_colon) {

				if (c == '\r' || c == '\n') {
					break;
				}

				if (i < maxLength - 1) {
					name[i++] = c;
				}
			}

			if (c == ':') {
				found_colon = true;
			}
		}
	}

	name[i] = '\0';
}


int BlueToothRepository::available() {

	return this->avrMicroRepository->available();
}


void BlueToothRepository::println(
	const char* message) {

	this->avrMicroRepository->println(message);
}


size_t BlueToothRepository::readString(
	char* buffer,
	size_t maxLength) {

	if (buffer == nullptr || maxLength == 0) {
		return 0;
	}

	size_t index = 0;

	const unsigned long timeout = 1000UL;
	const unsigned long quietTime = 20UL;

	const unsigned long start =
		this->avrMicroRepository->get_millis();

	unsigned long lastByteTime = start;

	bool receivedData = false;

	while (
		(this->avrMicroRepository->get_millis() - start)
		< timeout) {

		while (
			this->avrMicroRepository->available() > 0) {

			char c =
				(char)this->avrMicroRepository->read();

			if (index + 1 < maxLength) {
				buffer[index++] = c;
			}

			receivedData = true;

			lastByteTime =
				this->avrMicroRepository->get_millis();
		}

		if (
			receivedData &&
			(this->avrMicroRepository->get_millis() - lastByteTime)
			>= quietTime) {

			break;
		}
	}

	buffer[index] = '\0';

	return index;
}


void BlueToothRepository::flush() {

	this->avrMicroRepository->flush();
}