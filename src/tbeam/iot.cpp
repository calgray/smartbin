
#include "iot.h"

IoTMySQL::IoTMySQL(Client& client, const IPAddress& host, int port, char* usr, char* pwd)
: db((Client*)&client)
{
    if(db.connect(host, port, usr, pwd))
    {
        Serial.println("Connection success!");
        MySQL_Cursor cur_mem(&db);
        
        cur_mem.execute("use smartbin");
        constexpr char INSERT_DEVICE[] = "INSERT INTO devices VALUES (0, 'arduino-esp32', 1111)";
        cur_mem.execute(INSERT_DEVICE);
    }
    else
    {
        Serial.println("Connection failed!");
    }
}

IoTMySQL::~IoTMySQL()
{
    db.close();
}
