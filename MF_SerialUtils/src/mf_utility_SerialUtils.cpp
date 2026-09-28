#include <string.h> // Replace <cstring> with <string.h> for compatibility with some compilers
#include "mf_utility_SerialUtils.h"
#include <Arduino.h>
namespace SerialUtils {
	bool wait_for_pattern(AvrMicroRepository& repo,const char* pattern,size_t patternLen,unsigned long timeout) {
		unsigned long start = repo.get_millis();
		size_t pos = 0;
		while (repo.get_millis() - start < timeout) {
			if (repo.available()) {
				char c = repo.read();
				if (c == pattern[pos]) {
					if (++pos == patternLen) return true;
				}
				else {
					pos = (c == pattern[0]) ? 1 : 0;
				}
			}
		}
		return false;
	}
	bool wait_for_pattern(AvrMicroRepository& repo,const char* pattern,unsigned long timeout) {
		return wait_for_pattern(repo,pattern,static_cast<size_t>(strlen(pattern)),timeout);
	}

} 
