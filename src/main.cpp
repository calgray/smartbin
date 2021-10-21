/**
 * MIT License
 * 
 * Copyright (c) 2021 UWA-CITS5506-Gp01
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// setup() and loop() forward declared here
#include <Arduino.h>

#include "secrets.h"
#include "component/axp192.h"
#include "component/iot.h"
#include "component/neo6m.h"
#include "component/esp32_wifi.h"
#include "component/hcsr04.h"
#include "component/tmp36.h"
#include "component/scoped_switch.h"
#include "component/push_button.h"
#include "component/traffic_lights.h"
#include "component/debug_lights.h"
#include "board/tbeamv1.h"
#include <stream_extensions.h>

// Realtime clock persistent memory
RTC_DATA_ATTR double calibrationDistance = 0.0;

constexpr int EXTERN_PWR = 4;
constexpr int TRIG = 15;
constexpr int ECHO = 39; // VN
constexpr int RED = 14;
constexpr int YELLOW = 13;
constexpr int GREEN = 2;
constexpr int CALIBRATE = 38;
constexpr int TMP = 36; // VP

void setup()
{
    Serial.begin(115200); // USB Monitor
    Axp192 axp;
    Neo6M gps(Serial2);
    HCSR04 ultrasonic(TRIG, ECHO);
    TMP36 thermo(TMP);
    TrafficLights traffic(RED, YELLOW, GREEN);
    DebugLights debug(axp);
    ScopedSwitch scoped_switch(EXTERN_PWR);
    PushButton calibrate(CALIBRATE);
    sleep(1);

    if(calibrate.is_down())
    {
        // Calibration Mode
        // Note: Local calibration only necessary for traffic light volume display 
        // Calibration will be measured after 30 seconds
        for(int i = 0; i < 300; i++)
        {
            long delay = ultrasonic.measure_distance();
            std::optional<double> distance = ultrasonic.get_distance_m();
            if(calibrate.is_down())
            {
                // can realtime test distances and lights with io38 here
                if(distance.has_value())
                {
                    traffic.set_max_distance(distance.value());
                }
            }
            traffic.set_distance(distance.value());
            Serial << "dist: " << distance << ", pct: " << traffic.get_percent() << "\n";
            delayMicroseconds(std::max(0l, 100000l - delay));
        }

        calibrationDistance = ultrasonic.get_distance_m().value();
        traffic.set_max_distance(calibrationDistance);
        Serial << "Recalibrated distance to " << calibrationDistance << "\n";
    }
    else
    {
        // Load Calibration
        if(calibrationDistance == 0.0)
        {
            Serial << "Calibration distance not set, traffic module defaulting to " << traffic.get_max_distance() << "\n";
        }
        else
        {
            traffic.set_max_distance(calibrationDistance);
            Serial << "Calibrated distance is " << calibrationDistance << "\n";
        }
    }

    try
    {
        // Read Distance
        ultrasonic.measure_distance();
        std::optional<double> distance = ultrasonic.get_distance_m();
        traffic.set_distance(distance.has_value() ? distance.value() : 2.0);
        Serial << "dist: " << distance << ", pct: " << traffic.get_percent() << "\n";

        // Read Temperature
        float temp = thermo.read();
        Serial << "deg C: " << temp << "\n";

        // Read GPS
        gps.read(10000);
        std::optional<double> lat = gps.get_lat();
        std::optional<double> lng = gps.get_lng();
        Serial << "sat: " << gps.get_sat() << ", lat: " << lat << ", lng: " << lng << "\n"; 

        // Read Battery
        std::optional<double> voltage = axp.get_battery_voltage();
        axp.get_impl().debugCharging();
        Serial << "batt voltage: " << voltage << "\n";
        Serial << "batt discharge: " << axp.get_impl().getBattDischargeCurrent() << "\n";

        // Network Connect
        Esp32WiFi wifi(WIFI_SSID, WIFI_PWD);
        if (!wifi.is_connected())
        {
            throw std::runtime_error("failed to connected to wifi\n");
        }

        // IoT Record
        IoTMySQL iot(wifi.get_client(), DB_HOST, DB_PORT, DB_USR, DB_PWD);
        if(!iot.is_connected())
        {
            throw std::runtime_error("failed to connected to iot platform\n");
        }
        iot.insert_record(distance, temp, voltage, lat, lng);
        Serial << "Data record posted successfully\n";
        debug.disable_error();
    }
    catch(std::exception& e)
    {
        Serial << e.what() << "\n";
        debug.enable_error();
        sleep(3);
    }
}

void loop()
{
    Serial << "sleeping for 10s...\n";
#ifdef NOSLEEP
    setup();
#else
    esp_deep_sleep(10000000);
#endif
}
