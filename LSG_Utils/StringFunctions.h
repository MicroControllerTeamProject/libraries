#pragma once
#include <Arduino.h>
class StringFunctions
{
public:
	StringFunctions();
	~StringFunctions();
	char* ConcatString(char* fisrtString, char* secondString);
	String static SplitStringIndex(String data, char separator, int index);
};

