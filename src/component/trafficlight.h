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
    double get_percent() const { return _distance / _maxDistance; }

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
        if(percent < 0.33)
        {
            digitalWrite(_red, HIGH);
            digitalWrite(_yellow, LOW);
            digitalWrite(_green, LOW);
        }
        else if(percent < 0.66)
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