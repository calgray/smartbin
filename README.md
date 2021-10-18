
# SmartBin

SmartBin is an IoT ultrasonic low-power monitoring solution for waste disposal.

## Usage

The T-Beam board contains a 18650 battery holder and 3 physical switches PWR, IO38 and RST. After flashing the board press the RST and IO38 buttons together to start the maximum distance calibration.

Calibration using the current bin distance can be tested by subsequent presses of IO38 and checking the traffic lights.

Position the device on the empty bin and after 30 seconds calibration will be set.

## Setup

Connect the following modules pins to the respective T-Beam pins in main.cpp

Copy the secrets.h.in file to secret.h in the same folder and enter the wifi and database credentials

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
