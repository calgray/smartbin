#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WiFi.h>

class IoTMySQL
{
    MySQL_Connection db;

public:
    IoTMySQL(Client& network, const IPAddress& host, int port, char* usr, char* pwd);
    ~IoTMySQL();

    void post_device() {}
    void post_distance(double distance) {}
    void post_temperature() {}
    void post_location(double lat, double lng) {}
};
