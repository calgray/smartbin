
class TrafficLight
{
    int _red;
    int _yellow;
    int _green;
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

    void set_max_distance(double m) { _maxDistance = m; }
    void set_distance(double distance)
    {
        double percent = distance / _maxDistance;

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