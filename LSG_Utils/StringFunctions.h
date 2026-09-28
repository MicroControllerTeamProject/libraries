#pragma once
#include <Arduino.h>
class StringFunctions
{
public:
	StringFunctions();
	~StringFunctions();
	// Il risultato resta valido fino alla prossima ConcatString sullo stesso oggetto.
	char* ConcatString(const char* fisrtString, const char* secondString);
	String static SplitStringIndex(String data, char separator, int index);
private:
	char _concatResult[100] = {};
};

