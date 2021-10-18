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

class TrafficLight
{
    int _red;
    int _yellow;
    int _green;
    double _distance = 0.0;
    double _maxDistance = 0.5;
public:
    TrafficLight(const int red, const int yellow, const int green)
    : _red(red)
    , _yellow(yellow)
    , _green(green)
    {
        pinMode(_red, OUTPUT);
        pinMode(_yellow, OUTPUT);
        pinMode(_green, OUTPUT);
    }
    ~TrafficLight() {}


    double get_distance() const { return _distance; }
    double get_max_distance() const { return _maxDistance; }
    double get_percent() const { return 100.0 * _distance / _maxDistance; }

    void set_max_distance(double m)
    {
        _maxDistance = m;
        update_lights();
    }
    void set_distance(double distance)
    {
        _distance = distance;
        update_lights();
    }

private:
    void update_lights()
    {
        double percent = get_percent();
        if(percent < 33.3)
        {
            digitalWrite(_red, HIGH);
            digitalWrite(_yellow, LOW);
            digitalWrite(_green, LOW);
        }
        else if(percent < 66.6)
        {
            digitalWrite(_red, LOW);
            digitalWrite(_yellow, HIGH);
            digitalWrite(_green, LOW);
        }
        else
        {
            digitalWrite(_red, LOW);
            digitalWrite(_yellow, LOW);
            digitalWrite(_green, HIGH);
        }
    }
};