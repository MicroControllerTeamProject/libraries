#pragma once

#include <mf_repository_AvrMicroRepository.h>
#include <stddef.h> 
#define LITERAL_RETURN "\r\n"
#define LITERAL_OK "OK"

namespace SerialUtils {
    // versione principale (più specializzata)
    bool wait_for_pattern(AvrMicroRepository& repo,
        const char* pattern,
        size_t patternLen,
        unsigned long timeout);

    // overload “meno specializzato” (chiama la versione principale)
    bool wait_for_pattern(AvrMicroRepository& repo,
        const char* pattern,
        unsigned long timeout);
}

