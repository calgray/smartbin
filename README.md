
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

1. Install [PlatformIO](http://docs.platformio.org/page/core.html) and/or [PlatformIO IDE](https://platformio.org/platformio-ide) for VSCode:

`pip install platformio`

2. From the project repository directory run:

`platformio run -e ttgo-tbeam -t upload -t monitor`
