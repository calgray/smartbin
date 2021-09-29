/* ESPRESSIF MIT License
 * 
 * Copyright (c) 2018 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 * 
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef ESP_ARDUINO

#include <Arduino.h> // setup() and loop() forward declared here

#include "tbeamv1.h"
#include "secrets.h"
#include "tbeam/axp192.h"
#include "tbeam/iot.h"
#include "tbeam/neo6m.h"
#include "tbeam/esp32wifi.h"
#include "tbeam/trafficlight.h"
#include "tbeam/hcsr04.h"

void setup()
{
    Serial.begin(115200); // USB Monitor
    Axp192 axp;

    Esp32WiFi wifi(WIFI_SSID, WIFI_PWD);
    Neo6M gps;

    TrafficLight traffic;
    HCSR04 ultrasonic;
    double distance = ultrasonic.get_distance_m();
    traffic.set_max_distance(2.0);
    traffic.set_distance(distance);

    IoTMySQL iot(wifi.get_client(), DB_HOST_IP, DB_PORT, DB_USR, DB_PWD);
    iot.post_device();
    iot.post_distance(distance);
    iot.post_temperature();
    iot.post_location(gps.get().location.lat(), gps.get().location.lng());
}

void loop()
{
    //sleep(1);
    esp_deep_sleep(10000000);
}

#else
int main(int argc, char** argv) { }
#endif

