
class MQ2
{
    int _a0; // smoke pin

public:
    MQ2(int a0)
    : _a0(a0)
    {
        pinMode(_a0, INPUT);
    }

    ~MQ2() {}

    uint16_t get_smoke()
    {
        return analogRead(_a0);
    }
};
