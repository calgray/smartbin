

#include "neo6m.h"
#include "tbeamv1.h"
#include <HardwareSerial.h>
#include <TinyGPS++.h>

Neo6M::Neo6M()
{
    Serial2.begin(115200, SERIAL_8N1, GPS_RX, GPS_TX); // GPS Module
}

Neo6M::~Neo6M()
{
    Serial2.end();
}

const TinyGPSPlus& Neo6M::read()
{
    while(Serial2.available() > 0)
    {
        if(_gps.encode(Serial2.read()))
        {
            break;
        }
    }
    return _gps;
}

const TinyGPSPlus& Neo6M::get() const
{
    return _gps;
}
