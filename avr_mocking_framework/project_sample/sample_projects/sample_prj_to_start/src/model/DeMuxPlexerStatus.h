#pragma once
#include <stdint.h>
class DeMuxPlexerStatus{
public:
	DeMuxPlexerStatus::DeMuxPlexerStatus() {}
	bool en_status = false;
	uint8_t selected_chanell = 0;
};

