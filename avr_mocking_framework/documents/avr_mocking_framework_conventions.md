# AVR Mocking Framework Conventions

## Purpose
This note captures the conventions used in this repository so future projects follow the same structure without rediscovering the framework rules each time.

## Core Structure
Each new application project should follow this pattern:
- Arduino project for the real ATmega328 target
- separate Visual Studio test project
- shared business logic reused by both
- framework library classes injected into the business layer

Typical composition:
- `AvrMicroRepository`
- one or more `Activity` classes
- application business layer constructed with repository and activities

## Common Layer
The common layer is always part of the application structure:
- `mf_commons_commonsLayer.h`

It defines the compile-time flags and shared enums:
- `_ON_MOCKING_TESTS`
- `_DEBUG_FOR_SERIAL`
- `ProcessStatus`
- `AlarmTriggerOn`
- `PortDirection`
- `AnalogRefMode`
- `AnalogPortType`

## Compile-Time Rules
The intended usage is numeric compile-time switching.

Real Arduino target:
- `_ON_MOCKING_TESTS=0`
- `_DEBUG_FOR_SERIAL=0` by default
- set `_DEBUG_FOR_SERIAL=1` only when serial debug is really needed

Test target:
- `_ON_MOCKING_TESTS=1`
- `_DEBUG_FOR_SERIAL=0`

Use these flags to avoid carrying unnecessary code into the final embedded build.

### `_DEBUG_FOR_SERIAL`
Use `_DEBUG_FOR_SERIAL` to guard:
- `Serial.begin(...)`
- serial prints
- optional Arduino-only debug helpers

Pattern:
```cpp
#if _DEBUG_FOR_SERIAL
Serial.begin(9600);
#endif
```

### `_ON_MOCKING_TESTS`
Use `_ON_MOCKING_TESTS` to guard:
- test-only state
- test snapshots / fake support
- code that should exist only in host-side tests

Pattern:
```cpp
#if _ON_MOCKING_TESTS
TestOnlyState state;
#endif
```

## INO Guidelines For ATmega328
Keep the `.ino` minimal and memory-conscious.

Rules:
- never use `new`
- prefer static objects and static arrays of pointers
- avoid `String`
- avoid unnecessary serial code in production builds
- keep application constants minimal
- push logic into the business layer when possible
- use arrays of pointers for sensors because current sensors may grow in number

Preferred pattern for sensors:
```cpp
AnalogPortC current1(...);
AnalogPortC current2(...);
AnalogPortC* current_list[] = { &current1, &current2 };
```

## Naming Preferences
Prefer readable underscore-separated names for new project code when possible.

Rules:
- class names stay in `PascalCase`
- object instances should expose the concrete type in lowercase with underscores
- helper functions should prefer underscore-separated names
- arrays should end with `_list`
- counters should end with `_count`
- avoid long camelCase local names when a snake_case name is clearer
- do not rename existing framework APIs just to force style consistency

Examples:
- `software_serial_adapter`
- `analog_port_c_1`
- `analog_port_c_list`
- `analog_port_c_list_count`
- `current_alarm_if_above_threshold_for_seconds_list`
- `set_alarm_times_for_current_sensors()`

When working in legacy code or framework code, preserve the existing public API unless a dedicated refactor is requested.
## AppConfig Usage
`AppConfig.h` should stay close to the original project style.
It should contain only application-level constants that are truly shared and stable.

For the current project, keep it minimal.
Do not move every runtime choice into `AppConfig` if the original style kept that logic in the `.ino`.

Example of acceptable usage:
- offset sample count

Examples that should normally stay in the `.ino` when per-sensor customization is needed:
- per-sensor alarm seconds above threshold
- per-sensor alarm seconds under threshold

## Current Sensor Notes
Current sensors may be multiple, so the project must support arrays of sensor pointers.

For a centered current sensor:
- raw ADC is in the `0..1023` range
- resting centered value is typically around `512`
- after offset calibration, runtime values are centered near `0`

For initial framework validation, raw ADC and offset-compensated ADC are enough.
Full AC/RMS measurement logic is a later concern and is not required for the initial project scaffold.

## Original Sample Alignment
When creating a new project, prefer reusing the structure of the original sample project instead of inventing new conventions.

Specifically:
- keep the repository/activity/business pattern
- keep per-sensor configuration in the `.ino` when that matches the original sample
- keep `AppConfig` minimal
- keep the test project separate
- keep the `pch` setup in the test project for all Debug/Release and Win32/x64 configurations

## Visual Studio Test Project Rules
The test project should include:
- `pch.h`
- `pch.cpp`
- `src/extend.h`
- `fakeit.hpp`
- `NativeUnitTestProject` setup in `.vcxproj`

PCH must be configured in all test configurations:
- Debug|Win32
- Debug|x64
- Release|Win32
- Release|x64

`pch.cpp` must be the file that creates the precompiled header.

## Solution Layout
The solution should live in the macro folder, outside the two project folders.

Example:
- `MainsCurrentAnalyzer/`
- `MainsCurrentAnalyzer/mains_current_analyzer/`
- `MainsCurrentAnalyzer/mains_current_analyzer_test/`
- `MainsCurrentAnalyzer/MainsCurrentAnalyzer.sln`

## MainsCurrentAnalyzer Decisions Taken
For the `MainsCurrentAnalyzer` project:
- keep the macro folder under `project_sample`
- keep Arduino and test projects separate
- keep the solution in the macro folder root
- use `mf_commons_commonsLayer.h` explicitly in the new projects
- use `_DEBUG_FOR_SERIAL` and `_ON_MOCKING_TESTS` as the main compile-time gates
- keep the `.ino` minimal and static
- do not use `new`
- keep sensor declarations explicit and grouped into pointer arrays
- keep current alarm timing configurable per sensor in the `.ino`
- keep `AppConfig.h` minimal

## Important Working Rule
Do not modify legacy sample projects when aligning a new project to these conventions.
If a workaround is needed, contain it inside the new project whenever possible.
