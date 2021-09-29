#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WiFi.h>

class IoTMySQL
{
    MySQL_Connection db;

public:
    IoTMySQL(Client& client, const IPAddress& host, int port, char* usr, char* pwd);
    ~IoTMySQL();
};
