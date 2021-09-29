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
#include "axp192.h"
#include "iot.h"
#include "neo6m.h"
#include "esp32wifi.h"

// ESP32 sleep persistant memory
// RTC_DATA_ATTR double values[5];

void setup()
{
    Serial.begin(115200); // USB Monitor
    Axp192 axp();
    
    Esp32WiFi wifi(WIFI_SSID, WIFI_PWD);
    IoTMySQL iot(wifi.get_client(), DB_HOST_IP, DB_PORT, DB_USR, DB_PWD);
    Neo6M gps();
}

void loop() { sleep(1); }

#else

int main(int argc, char** argv)
{

}

#endif

