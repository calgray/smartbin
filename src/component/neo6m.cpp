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

#include "neo6m.h"
#include "board/tbeamv1.h"
#include <HardwareSerial.h>
#include <TinyGPS++.h>

Neo6M::Neo6M()
{
    Serial2.begin(9600, SERIAL_8N1, GPS_TX, GPS_RX); // GPS Module
}

Neo6M::~Neo6M()
{
    Serial2.end();
}

TinyGPSPlus& Neo6M::read()
{
    // see https://meshtastic.discourse.group/t/t-beam-v1-1-gps-access/775/8
    // see https://github.com/mikalhart/TinyGPSPlus/blob/master/examples/FullExample/FullExample.ino
    while(Serial2.available() > 0)
    {
        if(_gps.encode(Serial2.read()))
        {
            break;
        }
    }
    return _gps;
}

TinyGPSPlus& Neo6M::read(unsigned long ms)
{
    unsigned long start = millis();
    do
    {
        while (Serial2.available())
        {
            _gps.encode(Serial2.read());
        }
    } while (millis() - start < ms);
    return _gps;
}

TinyGPSPlus& Neo6M::get()
{
    return _gps;
}

void Neo6M::reset()
{
    byte reset_message[]={
        0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0xFF, 0xFF, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
        0x00, 0x00, 0x04, 0x1C, 0x9B
    };
    Serial2.write(reset_message, sizeof(reset_message));
}