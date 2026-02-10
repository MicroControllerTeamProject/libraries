#include <mf_repository_BlueToothRepository.h>
#include <Arduino.h> 
#include <stdlib.h>
#include <string.h>
#define ATPASSW_Q "AT+PSWD?"
#define ATPASSW_R "AT+PSWD="
#define ATRNAME_Q "AT+NAME?"
#define ATRNAME_R "AT+NAME="
#define ATROLE0 "AT+ROLE=0"
#define ATROLE1 "AT+ROLE=1"
#define ATCMODE0 "AT+CMODE=0"
#define ATUART9600 "AT+UART=9600,0,0"
#define ATVERSION_Q "AT+VERSION?"
//#define LITERAL_RETURN "\r\n"
//#define LITERAL_OK "OK"
bool is_in_program_mode = false;
bool is_in_receive_mode = false;
bool is_in_slave_mode = false;
bool is_in_master_mode = false;
#define OUTPUT 1
#define INPUT 0
BlueToothRepository::BlueToothRepository(AvrMicroRepository& avrMicroRepository, uint8_t blueToothKeyPin, unsigned long baudRateProgramMode, unsigned long baudRateReceveMode)
	: BlueToothRepository(avrMicroRepository, blueToothKeyPin, 255, baudRateProgramMode, baudRateReceveMode){}
BlueToothRepository::BlueToothRepository(AvrMicroRepository& avrMicroRepository,uint8_t blueToothKeyPin, uint8_t baseTransistorPin,unsigned long baudRateProgramMode, unsigned long baudRateReceveMode) {
	this->baseTransistorPin = baseTransistorPin;
	this->avrMicroRepository = &avrMicroRepository;
	this->blueToothKeyPin = blueToothKeyPin;
	this->baudRateProgramMode = baudRateProgramMode;
	this->baudRateReceveMode = baudRateReceveMode;
	this->avrMicroRepository->pinMode(this->blueToothKeyPin, OUTPUT); 
	this->avrMicroRepository->pinMode(this->baseTransistorPin, OUTPUT); 
}
BlueToothRepository::~BlueToothRepository() {
}
bool BlueToothRepository::is_device_detected(char* bt_address, char* device_name) {
	this->avrMicroRepository->clearBuffer();
	this->avrMicroRepository->print(ATRNAME_Q);
	this->avrMicroRepository->print(bt_address);
	this->avrMicroRepository->print(LITERAL_RETURN);
	char phone_name[32];
	uint16_t index = 0;
	unsigned long start = this->avrMicroRepository->get_millis();
	while (index < sizeof(phone_name) - 1
		&& (this->avrMicroRepository->get_millis() - start < 5000)) {
		if (this->avrMicroRepository->available()) {
			char c = this->avrMicroRepository->read();
			if (c == '\n' || c == '\r') {
				break; 
			}
			phone_name[index++] = c;
		}
	}
	phone_name[index] = '\0'; 
	if (strstr(phone_name, device_name) != nullptr) {
		return true;
	}
	else {
		return false;
	}
}
void BlueToothRepository::set_to_master_mode_v2() {
	if (!is_in_program_mode) {
		set_to_program_mode();
	}
	this->avrMicroRepository->print(ATROLE1);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 2000);
	this->avrMicroRepository->print(ATCMODE0);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 2000);
	is_in_master_mode = true;
	is_in_program_mode = true;
	is_in_receive_mode = false;

}
void BlueToothRepository::set_to_master_mode_v3() {
	this->avrMicroRepository->digitalWrite(this->baseTransistorPin, LOW);
	this->avrMicroRepository->delay(2000);
	this->avrMicroRepository->digitalWrite(this->blueToothKeyPin, HIGH);
	this->avrMicroRepository->delay(4000);
	this->avrMicroRepository->digitalWrite(this->baseTransistorPin, HIGH);
	this->avrMicroRepository->delay(3000);
	this->avrMicroRepository->begin(this->baudRateReceveMode);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 2000);
	is_in_master_mode = true;
	is_in_program_mode = false;
	is_in_receive_mode = true;
}
void BlueToothRepository::set_to_program_mode() {
	if (is_in_program_mode) return;
	this->avrMicroRepository->digitalWrite(this->blueToothKeyPin, 1);
	this->avrMicroRepository->digitalWrite(this->baseTransistorPin, 0);
	this->avrMicroRepository->delay(100);
	this->avrMicroRepository->digitalWrite(this->baseTransistorPin, 1);
	this->avrMicroRepository->delay(200);
	this->avrMicroRepository->begin(this->baudRateProgramMode);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 2000);
	is_in_program_mode = true;
	is_in_slave_mode = false;
}
void BlueToothRepository::turnOffBlueTooth() {
	if (baseTransistorPin == 255) return;
	this->avrMicroRepository->digitalWrite(this->baseTransistorPin, LOW);
	this->is_bluetooth_on = false;
}
void BlueToothRepository::turnOnBlueTooth() {
	if (baseTransistorPin == 255) return;
	this->avrMicroRepository->digitalWrite(this->baseTransistorPin, HIGH);
	this->is_bluetooth_on = true;
}
bool BlueToothRepository::isBluetoothOn() {
	return this->is_bluetooth_on;
}
void BlueToothRepository::set_to_receve_mode() {
	if (!is_in_slave_mode) return;
	this->avrMicroRepository->digitalWrite(this->blueToothKeyPin, LOW);
	this->avrMicroRepository->digitalWrite(this->baseTransistorPin, LOW);
	this->avrMicroRepository->delay(100);
	this->avrMicroRepository->digitalWrite(this->baseTransistorPin, HIGH);
	this->avrMicroRepository->delay(200);
	this->avrMicroRepository->begin(this->baudRateReceveMode);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 2000);
	is_in_receive_mode = true;
	is_in_program_mode = false;
}
void BlueToothRepository::set_to_slave_mode() {
	if (is_in_slave_mode) return;
	if (!is_in_program_mode) {
		this->set_to_program_mode();
	}
	this->avrMicroRepository->println(ATROLE0);
	//this->avrMicroRepository->delay(1500);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 1500);
	this->avrMicroRepository->println(ATUART9600);
	SerialUtils::wait_for_pattern(*this->avrMicroRepository, LITERAL_OK, 1500);
	//this->avrMicroRepository->delay(1500);
	is_in_slave_mode = true;
	is_in_master_mode = false;
	is_in_program_mode = false;
	this->set_to_receve_mode();
}
void BlueToothRepository::get_version(char* version) {
	if (!is_in_program_mode) {
		this->set_to_program_mode();
	}
	this->avrMicroRepository->clearBuffer();
	this->avrMicroRepository->println(ATVERSION_Q);
	int i = 0;
	unsigned long start = this->avrMicroRepository->get_millis();
	while (i < 3 && (this->avrMicroRepository->get_millis() - start < 1000)) {
		if (this->avrMicroRepository->available()) {
			char c = this->avrMicroRepository->read();
			if ((c >= '0' && c <= '9') || c == '.') {
				version[i++] = c;
			}
		}
	}
	version[i] = '\0';
}
void BlueToothRepository::get_current_password(char* currentPassword) {
	if (!is_in_program_mode) {
		this->set_to_program_mode();
	}
	this->avrMicroRepository->clearBuffer();
	this->avrMicroRepository->print(ATPASSW_Q);
	this->avrMicroRepository->print(LITERAL_RETURN);
	bool found_colon = false;
	int i = 0;
	unsigned long start = this->avrMicroRepository->get_millis();
	while ((this->avrMicroRepository->get_millis() - start < 1000)) {
		if (this->avrMicroRepository->available()) {
			char c = this->avrMicroRepository->read();
			if (found_colon) {
				if (i < 4 && c >= '0' && c <= '9') {
					currentPassword[i++] = c;
				}
				else if (i >= 4) {
					break; // finita la password
				}
			}
			if (c == ':') {
				found_colon = true; // Inizia lettura password
			}
		}
	}
	currentPassword[i] = '\0';
}
void BlueToothRepository::set_password(const char* pw) {
	// Assicurati di essere in program mode
	if (!is_in_program_mode) {
		set_to_program_mode();
	}
	// Svuota il buffer e invia il comando in due parti
	avrMicroRepository->clearBuffer();
	avrMicroRepository->print(ATPASSW_R);   // stringa costante
	avrMicroRepository->print(pw);           // la password
	avrMicroRepository->print(LITERAL_RETURN);       // CR+LF
	// Aspetta fino a 1s la sequenza "OK"
	unsigned long start = avrMicroRepository->get_millis();
	bool ok = false;
	uint8_t state = 0;  // 0 = cerca 'O', 1 = cercal 'K'
	while ((avrMicroRepository->get_millis() - start) < 1000 && !ok) {
		if (avrMicroRepository->available()) {
			char c = avrMicroRepository->read();
			if (state == 0) {
				// primo carattere di OK
				state = (c == 'O');
			}
			else {
				// secondo carattere di OK?
				if (c == 'K') {
					ok = true;
				}
				// se ricompare 'O', resto in stato 1, altrimenti torno a 0
				else {
					state = (c == 'O');
				}
			}
		}
	}
	// qui ok==true se abbiamo visto "OK" entro il timeout
	if (!ok) {
		// gestione del timeout (retry, log, ecc.)
	}
}
void BlueToothRepository::set_name(const char* name) {
	// 1) Vai in modalità program se non ci sei già
	if (!is_in_program_mode) {
		set_to_program_mode();
	}
	// 2) Svuota il buffer e invia il comando in tre parti
	avrMicroRepository->clearBuffer();
	avrMicroRepository->print(ATRNAME_R);  // costante in flash se usi F("…")
	avrMicroRepository->print(name);        // il nome da settare
	avrMicroRepository->print(LITERAL_RETURN);      // CR+LF

	unsigned long start = avrMicroRepository->get_millis();
	bool ok = false;
	uint8_t state = 0;  // 0 = aspetto 'O', 1 = aspetto 'K'

	while ((avrMicroRepository->get_millis() - start) < 1000 && !ok) {
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
					// se ricompare 'O' rimango in stato 1, altrimenti torno a 0
					state = (c == 'O');
				}
			}
		}
	}

	// 4) (opzionale) gestisci il timeout
	if (!ok) {
		// es. ritenta, logga, segnala errore...
	}
}
void BlueToothRepository::get_name(char* name) {
	if (!is_in_program_mode) {
		this->set_to_program_mode();
	}
	this->avrMicroRepository->clearBuffer();
	this->avrMicroRepository->print(ATRNAME_Q);
	this->avrMicroRepository->print(LITERAL_RETURN);

	bool found_colon = false;
	int i = 0;
	unsigned long start = this->avrMicroRepository->get_millis();
	while ((this->avrMicroRepository->get_millis() - start < 1000)) {
		if (this->avrMicroRepository->available()) {
			char c = this->avrMicroRepository->read();
			if (found_colon) {
				if (c == '\r' || c == '\n') {
					break; // fine nome
				}
				name[i++] = c;
			}
			if (c == ':') {
				found_colon = true; // inizia lettura nome
			}
		}
	}
	name[i] = '\0';
}












