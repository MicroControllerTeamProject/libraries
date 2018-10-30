#include "StringFunctions.h"
#include <Arduino.h>
#include <pins_arduino.h>


StringFunctions::StringFunctions()
{
}


StringFunctions::~StringFunctions()
{
}


char* StringFunctions::ConcatString(char* fisrtString, char* secondString)
{
	char result[100];   // array to hold the result.
	strcpy(result, fisrtString); // copy string one into the result.
	strcat(result, secondString); // append string two to the result.
	return result;
}

String StringFunctions::SplitStringIndex(String data, char separator, int index)
{
	int found = 0;
	int strIndex[] = { 0, -1 };
	int maxIndex = data.length() - 1;

	for (int i = 0; i <= maxIndex && found <= index; i++) {
		if (data.charAt(i) == separator || i == maxIndex) {
			found++;
			strIndex[0] = strIndex[1] + 1;
			strIndex[1] = (i == maxIndex) ? i + 1 : i;
		}
	}
	return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
