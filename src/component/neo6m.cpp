

#include "neo6m.h"
#include "tbeamv1.h"
#include <HardwareSerial.h>
#include <TinyGPS++.h>

Neo6M::Neo6M()
{
    Serial2.begin(9600, SERIAL_8N1, GPS_TX, GPS_RX); // GPS Module
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

TinyGPSPlus& Neo6M::read(unsigned long ms)
{
    unsigned long start = millis();
    do
    {
        while (Serial2.available())
        {
            _gps.encode(Serial2.read());
        }
    } while (millis() - start < ms);
    return _gps;
}

TinyGPSPlus& Neo6M::get()
{
    return _gps;
}

void Neo6M::reset()
{
    byte reset_message[]={
        0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0xFF, 0xFF, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
        0x00, 0x00, 0x04, 0x1C, 0x9B
    };
    Serial2.write(reset_message, sizeof(reset_message));
}