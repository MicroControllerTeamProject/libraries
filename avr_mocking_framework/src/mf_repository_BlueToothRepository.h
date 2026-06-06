#pragma once
#include <mf_repository_AvrMicroRepository.h>
#include <mf_utility_SerialUtils.h>
class BlueToothRepository{
public:
	BlueToothRepository(AvrMicroRepository& avrMicroRepository,
		uint8_t blueToothKeyPin,unsigned long baudRateProgramMode, 
		unsigned long baudRateReceveMode);
	BlueToothRepository(AvrMicroRepository& avrMicroRepository,
		uint8_t blueToothKeyPin, uint8_t baseTransistorPin, 
		unsigned long baudRateProgramMode,unsigned long baudRateReceveMode);
	virtual ~BlueToothRepository();
	virtual bool is_device_detected(char* bt_address, char* device_name);
	/*virtual bool is_device_detected(const char* bt_address);*/
	virtual void set_to_slave_mode();
	virtual void set_to_master_mode_v2();
	virtual void set_to_master_mode_v3();
	virtual void turnOffBlueTooth();
	virtual void turnOnBlueTooth();
	virtual bool isBluetoothOn();
	virtual void set_to_program_mode();
	virtual void get_version(char* versionOut);
	virtual void get_current_password(char* currentPassword);
	virtual void set_password(const char* newPassword);
	virtual void set_name(const char* name);
	virtual void get_name(char* buf);
private:
	AvrMicroRepository* avrMicroRepository = nullptr;
	void set_to_receve_mode();
	bool is_master_mode = false;
	uint8_t blueToothKeyPin; // Pin per il tasto del Bluetooth
	uint8_t baseTransistorPin; // Pin per il transistor di base
	unsigned long baudRateProgramMode = 38400; // Baud rate per la modalità di programmazione
	unsigned long baudRateReceveMode = 9600; // Baud rate per la modalità di ricezione
	bool is_bluetooth_on = false; // Stato del Bluetooth (0 = spento, 1 = acceso)
};

