

#include <circular_queue/circular_queue_mp.h>

#include <vector>
#include <queue>

class HCSR04
{
public:
    HCSR04() {}
    ~HCSR04() {}

    double get_distance_m() const { return 1.0; }
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
