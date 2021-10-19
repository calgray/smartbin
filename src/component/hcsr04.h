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

#include <vector>
#include <queue>
#include <optional>

class HCSR04
{
    int _trig;
    int _echo;
    std::optional<double> _distance;
public:
    HCSR04(const int trig, const int echo)
    : _trig(trig)
    , _echo(echo)
    , _distance()
    {
        pinMode(_trig, OUTPUT);
        pinMode(_echo, INPUT);
        // the first reading is always zero 
        measure_distance();
    }

    ~HCSR04() {}

    std::optional<double> get_distance_m() const { return _distance.value(); }
    
    double measure_distance()
    {
        digitalWrite(_trig, LOW);
        delayMicroseconds(2);
        digitalWrite(_trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(_trig, LOW);
        long dur = pulseIn(_echo, HIGH, 100000);
        if (dur < 1000000)
        {
            _distance = dur / 5820.0;
        }
        else
        {
            _distance.reset();
        }
        return dur;
    }
};
