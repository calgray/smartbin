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

#include <hcsr04.h>
#include <axp20x.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <TinyGPS++.h>
#include <WiFi.h>

// ESP32 sleep persistant memory
// RTC_DATA_ATTR double values[5];

AXP20X_Class axp;
WiFiClient client;
MySQL_Connection db((Client*)&client);

void setup()
{
    Serial.begin(115200); // USB Monitor

    Wire.begin(SDA, SCL); // Power Module
    axp.begin(Wire, AXP192_SLAVE_ADDRESS);
    //axp.setPowerOutPut(AXP192_DCDC1, AXP202_ON); // OLED
    //axp.setPowerOutPut(AXP192_DCDC2, AXP202_ON); // None
    //axp.setPowerOutPut(AXP192_DCDC3, AXP202_ON); // 3.3V Pin, pin7, pin11
    //axp.setPowerOutPut(AXP192_LDO2, AXP202_ON); // LoRa
    axp.setPowerOutPut(AXP192_LDO3, AXP202_ON); // GPS


    Serial2.begin(115200, SERIAL_8N1, GPS_RX, GPS_TX); // GPS Module

    // WiFi
    WiFi.begin(WIFI_SSID, WIFI_PWD);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    // MySQL
    if (db.connect(host_ip, port, usr, pwd))
    {
        Serial.println("Connection success!");
        auto cur_mem = std::auto_ptr<MySQL_Cursor>( new MySQL_Cursor(&db));
        
        cur_mem->execute("use smartbin");
        constexpr char INSERT_DEVICE[] = "INSERT INTO devices VALUES (0, 'arduino-esp32', 1111)";
        cur_mem->execute(INSERT_DEVICE);
    }
    else
    {
        Serial.println("Connection failed!");
    }
    db.close();

    axp.setPowerOutPut(AXP192_LDO3, AXP202_OFF);
}

void loop() { sleep(1); }

#else

int main(int argc, char** argv)
{

}

#endif

