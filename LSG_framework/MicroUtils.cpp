#include <MicroUtils.h>

String MicroUtils::getBatteryGrafBarLevel(float batteryVoltageLevel)
{
	if (batteryVoltageLevel <= 3.25)
		return F("[    ]o");
	if (batteryVoltageLevel <= 3.30)
		return F("[|   ]o");
	if (batteryVoltageLevel <= 3.60)
	if (batteryVoltageLevel <= 3.40)
		return F("[||  ]o");
		return F("[||| ]o");
	if (batteryVoltageLevel <= 5.50)
		return F("[||||]o");
}

float MicroUtils::internalTemperature(unsigned int offset)
{
	unsigned int wADC;
	double t;
	// The internal temperature has to be used
	// with the internal reference of 1.1V.
	// Channel 8 can not be selected with
	// the analogRead function yet.

	// Set the internal reference and mux.
	ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
	ADCSRA |= _BV(ADEN);  // enable the ADC

	delay(20);            // wait for voltages to become stable.

	ADCSRA |= _BV(ADSC);  // Start the ADC
						  // Detect end-of-conversion
	while (bit_is_set(ADCSRA, ADSC));

	// Reading register "ADCW" takes care of how to read ADCL and ADCH.
	wADC = ADCW;

	// The offset of 324.31 could be wrong. It is just an indication.
	t = (wADC - offset) / 1.22;

	// The returned temperature is in degrees Celsius.
	return (t);
}