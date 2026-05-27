#pragma once
#include <stdint.h>
class DeMuxPlexerEntity{
public:
	DeMuxPlexerEntity::DeMuxPlexerEntity() {}
	bool en_status = false;
	uint8_t selected_chanell = 0;
};

