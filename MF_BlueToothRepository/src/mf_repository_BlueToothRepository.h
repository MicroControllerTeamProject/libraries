#pragma once

#include <mf_commons_commonsLayer.h>
#include <mf_repository_AvrMicroRepository.h>
#include <mf_utility_SerialUtils.h>

class BlueToothRepository {

public:

	BlueToothRepository(
		AvrMicroRepository& avrMicroRepository,
		uint8_t blueToothKeyPin,
		unsigned long baudRateProgramMode,
		unsigned long baudRateReceveMode);

	BlueToothRepository(
		AvrMicroRepository& avrMicroRepository,
		uint8_t blueToothKeyPin,
		uint8_t baseTransistorPin,
		unsigned long baudRateProgramMode,
		unsigned long baudRateReceveMode);


#if _ON_MOCKING_TESTS

	virtual ~BlueToothRepository();

	virtual bool is_device_detected(
		const char* bt_address,
		const char* device_name);

	virtual void set_to_slave_mode();

	virtual void find_mode_v3();

	virtual void set_to_master_mode();

	virtual void turnOffBlueTooth();

	virtual void turnOnBlueTooth();

	virtual bool isBluetoothOn();

	virtual void set_to_program_mode();

	virtual void get_version(
		char* versionOut,
		uint8_t maxLength);

	virtual void get_current_password(
		char* currentPassword,
		uint8_t maxLength);

	virtual void set_password(
		const char* newPassword);

	virtual void set_name(
		const char* name);

	virtual void get_name(
		char* name,
		uint8_t maxLength);

	virtual int available();

	virtual void println(
		const char* message);

	virtual size_t readString(
		char* buffer,
		size_t maxLength);

	virtual void flush();


#else

	~BlueToothRepository();

	bool is_device_detected(
		const char* bt_address,
		const char* device_name);

	void set_to_slave_mode();

	void set_to_master_mode();

	void find_mode_v3();

	void turnOffBlueTooth();

	void turnOnBlueTooth();

	bool isBluetoothOn();

	void set_to_program_mode();

	void get_version(
		char* versionOut,
		uint8_t maxLength);

	void get_current_password(
		char* currentPassword,
		uint8_t maxLength);

	void set_password(
		const char* newPassword);

	void set_name(
		const char* name);

	void get_name(
		char* name,
		uint8_t maxLength);

	int available();

	void println(const char* message);
	size_t readString(char* buffer,size_t maxLength);
	void flush();
#endif
private:

	AvrMicroRepository* avrMicroRepository = nullptr;

	void set_to_receive_mode();

	bool is_in_program_mode = false;

	bool is_in_receive_mode = false;

	bool is_in_slave_mode = false;

	bool is_in_master_mode = false;

	uint8_t blueToothKeyPin;

	uint8_t baseTransistorPin;

	unsigned long baudRateProgramMode = 38400;

	unsigned long baudRateReceveMode = 9600;

	bool is_bluetooth_on = false;
};