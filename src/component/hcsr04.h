

#include <circular_queue/circular_queue_mp.h>

#include <vector>
#include <queue>

class HCSR04
{
    int _trig;
    int _echo;
    double _distance;
public:
    HCSR04(const int trig, const int echo)
    : _trig(trig)
    , _echo(echo)
    , _distance(0)
    {
        pinMode(_trig, OUTPUT);
        pinMode(_echo, INPUT);
    }

    ~HCSR04() {}

    double get_distance_m() const { return _distance; }
    
    double measure_distance()
    {
        digitalWrite(_trig, LOW);
        delayMicroseconds(2);
        digitalWrite(_trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(_trig, LOW);
        long dur = pulseIn(_echo, HIGH, 100000);
        _distance = dur / 5820.0;
        return dur;
    }
};


class HCSR04Buffered
{
    circular_queue_mp<double> m_buffer;
public:
    HCSR04Buffered(int size)
    : m_buffer(size)
    { }

    double get_value()
    {
        double total = 0.0;
        int count = 0;
        m_buffer.for_each_requeue([&](double& x) {
            total += x;
            count++;
            return false;
        });
        return total / count;
    }
};
