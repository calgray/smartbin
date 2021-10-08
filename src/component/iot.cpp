
#include "iot.h"
#include <lwip/dns.h>
#include <sstream>

IoTMySQL::IoTMySQL(Client& network, const char* host, int port, char* usr, char* pwd)
: _db(&network)
, _cursor(nullptr)
{
    std::future<IPAddress> future = _dns_promise.get_future();
    ip_addr_t host_ip;
    err_t err = dns_gethostbyname(host, &host_ip, &dns_found, this);
    if(err != 0 && err != -5)
    {
        Serial.printf("error: %i\n", err);
    }
    IPAddress host_ip2 = future.get(); // Blocks until future is joined
    Serial.printf("Connecting to db at %i.%i.%i.%i:%i\n", host_ip2[0], host_ip2[1], host_ip2[2], host_ip2[3], port);

    if(_db.connect(host_ip2, port, usr, pwd))
    {
        Serial.println("Connection success!");
        _cursor = new MySQL_Cursor(&_db);
        _cursor->execute("USE smartbin;");
    }
    else
    {
        Serial.println("Connection failed!");
        throw std::exception();
    }
}

void IoTMySQL::dns_found(const char *name, const ip_addr_t *ipaddr, void *callback_arg)
{
    Serial.printf("dns resolved\n");
    IoTMySQL* iot = (IoTMySQL*)callback_arg;
    IPAddress ip(ipaddr->u_addr.ip4.addr);
    iot->_dns_promise.set_value(ip);
}

IoTMySQL::~IoTMySQL()
{
    if (_cursor != nullptr)
    {
        delete _cursor;
        _cursor = nullptr;
    }
    _db.close();
}

bool IoTMySQL::is_connected() const
{
    return _cursor != nullptr;
}

void IoTMySQL::insert_device()
{
    //constexpr char INSERT_DEVICE[] = "INSERT INTO devices VALUES (0, 'arduino-esp32', 1111);";
    //_cursor->execute(INSERT_DEVICE);
}

void IoTMySQL::insert_record(double distance, double temp, double battery, double lat, double lng)
{
    std::stringstream ss;
    ss << "INSERT INTO distances (device_id, distance, temperature, battery, lat, lng)";
    ss << " VALUES (1, " << distance << ", " << temp << ", " << battery << ", " << lat << ", " << lng << ");";
    if(!_cursor->execute(ss.str().c_str()))
    {
        throw std::runtime_error("insert_data failed");
    }
}
