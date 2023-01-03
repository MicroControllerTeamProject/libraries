#include "NTC3950thermistorActivity.h"

NTC3950thermistorActivity::NTC3950thermistorActivity(AnalogPort** analogPort, float vref, commonsLayer::analogRefMode mode, uint8_t analogPortsNumber, float r1_voltageResistor) : DeviceActivity(analogPort, vref, mode, analogPortsNumber)
{
	this->R_1 = r1_voltageResistor;
}

bool NTC3950thermistorActivity::isThereAnyPortsOnAlarm(AvrMicroRepository& avrMicroRepository)
{
	for (int i = 0; i < this->getAnalogPortsNumber(); i++)
	{
		// loop over several values to lower noise
		float T_sum = 0.0;
		for (int ii = 0; ii < this->avg_size; ii++) {
			// read the input on analog pin 0:

			float voltage = this->analogReadVoltageByPin(this->analogPort[i]->getPin(), avrMicroRepository);

			// this is where the thermistor conversion happens based on parameters from fit
			T_sum += (-1.0 / this->b) * (log(((this->R_1 * voltage) / (this->a * (this->getVref() - voltage))) - (this->c / this->a)));
		}

		// averaging values from loop
		float T_approx = T_sum / float(avg_size);
		if (T_approx > this->analogPort[i]->maxUnitOfMisureAlarmValue) return true;
		if (T_approx < this->analogPort[i]->minUnitOfMisureAlarmValue) return true;
	}
return false;

	//// readout for Celsius and Fahrenheit
	//Serial.print("Temperature: ");
	//Serial.print(T_approx);
	//Serial.print(" (");
	//Serial.print((T_approx * (9.0 / 5.0)) + 32.0);
	//Serial.println(" F)");
	/*delay(500);*/
}

