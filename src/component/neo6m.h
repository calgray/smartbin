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

#pragma once

#include <TinyGPS++.h>
#include <optional>

class HardwareSerial;

class Neo6M
{
    HardwareSerial& _serial;
    TinyGPSPlus _gps;
public:
    /**
     * @brief Construct a new Neo-6M object
     * AXP192_LDO3 must be enabled if axp not provided
     */
    Neo6M(HardwareSerial& serial);
    ~Neo6M();

    /**
     * @brief Reads the UART Serial into TinyGPS
     * until unavailable and returns the result.
     * 
     * @return const TinyGPSPlus&
     */
    TinyGPSPlus& read();

    /**
     * @brief Reads the UART Serial for a given time window
     * and returns the result.
     * 
     * @param ms 
     * @return TinyGPSPlus& 
     */
    TinyGPSPlus& read(unsigned long ms);

    TinyGPSPlus& get();

    std::optional<double> get_lat()
    {
        std::optional<double> lat;
        if(_gps.location.isValid())
        {
            lat = _gps.location.lat();
        }
        return lat;
    }
    std::optional<double> get_long()
    {
        std::optional<double> lng;
        if(_gps.location.isValid())
        {
            lng = _gps.location.lng();
        }
        return lng;
    }

    void reset();
};