

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

TinyGPSPlus& Neo6M::get()
{
    return _gps;
}
