#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WiFi.h>
#include <future>

class IoTMySQL
{
    std::promise<IPAddress> _dns_promise;
    MySQL_Connection _db;
    MySQL_Cursor* _cursor;

public:
    IoTMySQL(Client& network, const char* host, int port, char* usr, char* pwd);
    static void dns_found(const char *name, const ip_addr_t *ipaddr, void *callback_arg);
    ~IoTMySQL();

    bool is_connected() const;
    void insert_device();
    void insert_record(double distance, double temp, double battery, double lat, double lng);
};
