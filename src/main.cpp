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
#include "component/axp192.h"
#include "component/iot.h"
#include "component/neo6m.h"
#include "component/esp32wifi.h"
#include "component/trafficlight.h"
#include "component/hcsr04.h"
#include "component/mq2.h"
#include "component/tmp36.h"

void setup()
{
    Serial.begin(115200); // USB Monitor
    Axp192 axp;

    constexpr int RED = 14;
    constexpr int YELLOW = 13;
    constexpr int GREEN = 2;
    TrafficLight traffic(RED, YELLOW, GREEN);
    traffic.set_max_distance(0.5);

    constexpr int TRIG = 15;
    constexpr int ECHO = 39;
    HCSR04 ultrasonic(TRIG, ECHO);

    constexpr int TMP = 36;
    TMP36 thermo(TMP);

    //constexpr int GASA0 = 4;
    //MQ2 gas(GASA0);

    constexpr int ONBOARD_LED = 4;
    pinMode(ONBOARD_LED, OUTPUT);
    digitalWrite(ONBOARD_LED, HIGH); // Turns onboard LED off
    axp.getimpl().setChgLEDMode(axp_chgled_mode_t::AXP20X_LED_OFF);

    Neo6M gps;
    gps.read(1000);
    Serial.printf("sat: %i, lat: %f, long %f\n",
        gps.get().satellites.value(),
        gps.get().location.lat(),
        gps.get().location.lng());


    double distance;
    for(int i = 0; i < 5; i++)
    {
        long delay = ultrasonic.measure_distance();
        distance = ultrasonic.get_distance_m();
        Serial.printf("dist: %f , pct: %f\n", distance, distance / 0.5);
        traffic.set_distance(distance);
        delayMicroseconds(std::max(0l, 100000l - delay));
    }
    float temp = thermo.read();
    Serial.printf("deg C: %f\n", temp);

    // IoT
    // Esp32WiFi wifi(WIFI_SSID, EAP_ID, EAP_USR, EAP_PWD);
    Esp32WiFi wifi(WIFI_SSID, WIFI_PWD);
    if (!wifi.is_connected())
    {
        Serial.printf("failed to connected to wifi\n"); digitalWrite(4, LOW);
    }
    else
    {
        IoTMySQL iot(wifi.get_client(), DB_HOST, DB_PORT, DB_USR, DB_PWD);
        if(!iot.is_connected())
        {
            Serial.printf("failed to connected to iot platform\n"); digitalWrite(4, LOW);
        }
        else
        {
            try
            {
                iot.insert_device();
                iot.insert_distance(distance);
                iot.insert_temperature(temp);
                iot.update_location(gps.get().location.lat(), gps.get().location.lng());
                digitalWrite(4, HIGH);
            }
            catch(std::exception& e)
            {
                Serial.println(e.what());
                digitalWrite(4, LOW);
            }
        }
    }
}

void loop()
{
    sleep(5);
    Serial.printf("sleeping for 300s...\n");
    esp_deep_sleep(300000000);
}

#endif
