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

#include "main.h"

#ifdef ESP_ARDUINO

// setup() and loop() forward declared here
#include <Arduino.h>

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

RTC_DATA_ATTR double calibrationDistance = 0.0;

constexpr int EXTERN_PWR = 21;
constexpr int TRIG = 15;
constexpr int ECHO = 39;
constexpr int RED = 14;
constexpr int YELLOW = 13;
constexpr int GREEN = 2;
constexpr int CALIBRATE = 38;
constexpr int TMP = 36;

bool read_io38()
{
    return digitalRead(38) == LOW;
}

void setup()
{
    Serial.begin(115200); // USB Monitor
    Axp192 axp;
    Neo6M gps;
    HCSR04 ultrasonic(TRIG, ECHO);
    TrafficLight traffic(RED, YELLOW, GREEN);
    TMP36 thermo(TMP);


    pinMode(CALIBRATE, INPUT);

    pinMode(EXTERN_PWR, OUTPUT);
    digitalWrite(EXTERN_PWR, HIGH);

    pinMode(ONBOARD_LED, OUTPUT);
    digitalWrite(ONBOARD_LED, LOW);

    pinMode(ONBOARD_LED, OUTPUT);
    digitalWrite(ONBOARD_LED, HIGH); // Turns onboard LED off
    axp.getimpl().setChgLEDMode(axp_chgled_mode_t::AXP20X_LED_OFF);

    // Calibration Mode
    // Note: Local calibration only necessary for traffic light display 
    if(read_io38())
    {
        // Will calibrate in 20 seconds
        for(int i = 0; i < 200; i++)
        {
            long delay = ultrasonic.measure_distance();
            double distance = ultrasonic.get_distance_m();
            if(read_io38())
            {
                // can realtime demo distances with io38 here
                // calibration will be set after 20 seconds regardless
                traffic.set_max_distance(distance);
            }
            traffic.set_distance(distance);
            Serial.printf("dist: %f , pct: %f\n", distance, traffic.get_percent());
            delayMicroseconds(std::max(0l, 100000l - delay));
        }

        calibrationDistance = ultrasonic.get_distance_m();
        traffic.set_max_distance(calibrationDistance);
        Serial.printf("Recalibrated distance to %f\n", calibrationDistance);
    }
    else
    {
        if(calibrationDistance == 0.0)
        {
            Serial.printf("Calibration distance not set, traffic module defaulting to %f\n", traffic.get_max_distance());
        }
        else
        {
            traffic.set_max_distance(calibrationDistance);
            Serial.printf("Calibrated distance is %f\n", calibrationDistance);
        }
    }

    // Read Distance
    double distance;
    long delay = ultrasonic.measure_distance();
    distance = ultrasonic.get_distance_m();
    traffic.set_distance(distance);
    Serial.printf("dist: %f , pct: %f\n", distance, traffic.get_percent());
    delayMicroseconds(std::max(0l, 100000l - delay));


    // Read Temperature
    float temp = thermo.read();
    Serial.printf("deg C: %f\n", temp);

    // Read GPS
    gps.read(1000);
    Serial.printf("sat: %i, lat: %f, long %f\n",
        gps.get().satellites.value(),
        gps.get().location.lat(),
        gps.get().location.lng());

    // Read Battery
    axp.getimpl().debugCharging();
    Serial.printf("batt voltage: %f\n", axp.getimpl().getBattVoltage());
    Serial.printf("batt percentage: %i\n", axp.getimpl().getBattPercentage());
    Serial.printf("batt discharge: %f\n", axp.getimpl().getBattDischargeCurrent());

    // IoT Record
    try
    {
        // Esp32WiFi wifi(WIFI_SSID, EAP_ID, EAP_USR, EAP_PWD);
        Esp32WiFi wifi(WIFI_SSID, WIFI_PWD);
        if (!wifi.is_connected())
        {
            Serial.printf("failed to connected to wifi\n");
            enable_error_light(axp);
        }
        else
        {
            IoTMySQL iot(wifi.get_client(), DB_HOST, DB_PORT, DB_USR, DB_PWD);
            if(!iot.is_connected())
            {
                Serial.printf("failed to connected to iot platform\n");
                enable_error_light(axp);
            }
            else
            {
                iot.insert_record(
                    distance,
                    temp,
                    axp.getimpl().getBattVoltage() / 1000.0f,
                    gps.get().location.lat(),
                    gps.get().location.lng()
                );
                Serial.println("Data record posted successfully");
                disable_error_light(axp);
            }
        }
    }
    catch(std::exception& e)
    {
        Serial.println(e.what());
        enable_error_light(axp);
    }
}

void loop()
{
    digitalWrite(EXTERN_PWR, LOW);
    sleep(5);
    Serial.printf("sleeping for 10s...\n");
    esp_deep_sleep(10000000);
}

void enable_error_light(Axp192& axp)
{
    axp.getimpl().setChgLEDMode(axp_chgled_mode_t::AXP20X_LED_BLINK_1HZ);
    digitalWrite(ONBOARD_LED, LOW); // LOW is on
}

void disable_error_light(Axp192& axp)
{
    axp.getimpl().setChgLEDMode(axp_chgled_mode_t::AXP20X_LED_OFF);
    digitalWrite(ONBOARD_LED, HIGH); // HIGH is off
}

#endif
