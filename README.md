
# SmartBin

SmartBin is an IoT ultrasonic low-power monitoring solution for waste disposal.

## Usage

TBeam contains

## Setup

Connect the following modules pins to the respective T-Beam pins in main.cpp

Copy the secrets.h.in file to secret.h in the same folder and enter the wifi and database credentials

### Record without calibration

Press the reset pin to make a recording, the board will turn on a red LED if there is a connection issue.

### Record with Calibrate

Hold the IO38 button down whilst tapping the reset pin. The board will enter calibration mode for 10 seconds where subsequent taps
to IO38 will set the calibration distance.

## Build

Install PlatformIO and/or PlatformIO VSCode integration.

`pip install platformio`

in the project directory run:

`platformio run -e ttgo-tbeam`

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
