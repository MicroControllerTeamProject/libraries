#include "StringFunctions.h"
#include <Arduino.h>
#include <pins_arduino.h>


StringFunctions::StringFunctions()
{
}


StringFunctions::~StringFunctions()
{
}


char* StringFunctions::ConcatString(const char* fisrtString, const char* secondString)
{
	if (fisrtString != _concatResult)
	{
		strncpy(_concatResult, fisrtString, sizeof(_concatResult) - 1);
		_concatResult[sizeof(_concatResult) - 1] = '\0';
	}
	strncat(_concatResult, secondString, sizeof(_concatResult) - strlen(_concatResult) - 1);
	return _concatResult;
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
