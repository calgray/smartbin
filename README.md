
# SmartBin

SmartBin is an IoT ultrasonic low-power monitoring solution for waste disposal.

## Build

Install PlatformIO and/or PlatformIO VSCode integration.

`pip install platformio`

in the project directory run:

`platformio run build -e ttgo-tbeam`

## Continuous Integration

Use github actions, read tests/README

### Tests

Tests can be run using command:

`platformio test -e ttgo-tbeam`

Tests compatible with the native machine can be run using:

`platformio test -e native`

### C/C++ Linters

Flawfinder
Klocwork
Coverity
CodeSonar
