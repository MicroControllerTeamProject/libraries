// File: commonsLayer.h
#pragma once
#ifndef _ON_MOCKING_TESTS 
#define _ON_MOCKING_TESTS 1
#endif
#ifndef _DEBUG_FOR_SERIAL
#define _DEBUG_FOR_SERIAL 0
#endif
namespace mf::commons::commonsLayer {
	enum class ProcessStatus { blocked_level_too_high = 0, blocked_level_to_low = 1, blocked_level_missing = 2, stopped = 3, running = 4 };
	enum class AlarmTriggerOn { noset = -1, low = 0, high = 1 };
	enum class PortDirection : int8_t { noset = -1, input = 0, output = 1,input_pullup = 2 };
	enum class AnalogRefMode { EXTERNAL_m = 0, DEFAULT_m = 1, INTERNAL_m = 3, INTERNAL1V1_m = 4, INTERNAL2V56_m = 5 };
	enum class AnalogPortType { custom_misure = 0, digital = 1, voltage = 2 };
}
