
#include "iot.h"
#include <lwip/dns.h>
#include <sstream>

IoTMySQL::IoTMySQL(Client& network, const char* host, int port, char* usr, char* pwd)
: _db(&network)
, _cursor(nullptr)
{
    std::future<void> future = _dns_promise.get_future();
    ip_addr_t host_ip;
    err_t err = dns_gethostbyname(host, &host_ip, &dns_found, this);
    if(err != 0 && err != -5)
    {
        Serial.printf("error: %i\n", err);
    }
    future.wait();

    IPAddress host_ip2(host_ip.u_addr.ip4.addr);
    Serial.printf("Connecting to db at %i.%i.%i.%i:%i\n", host_ip2[0], host_ip2[1], host_ip2[2], host_ip2[3], port);
    host_ip2[0] = 167;
    host_ip2[1] = 99;
    host_ip2[2] = 72;
    host_ip2[3] = 151;
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
    Serial.printf("dns found!\n");
    IoTMySQL* iot = (IoTMySQL*)callback_arg;
    iot->_dns_promise.set_value();
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

void IoTMySQL::insert_distance(double distance)
{
    std::stringstream ss;
    ss << "INSERT INTO distances (device_id, distance) VALUES (1, " << distance << ");";
    //_cursor->execute(ss.str().c_str());
    if(!_cursor->execute(ss.str().c_str()))
    {
        throw std::runtime_error("insert_temperature failed");
    }
}

void IoTMySQL::insert_temperature(float temp)
{
    std::stringstream ss;
    ss << "INSERT INTO temperature (device_id, temp_celcius) VALUES (1, " << temp << ");";
    //_cursor->execute(ss.str().c_str());
    if(!_cursor->execute(ss.str().c_str()))
    {
        throw std::runtime_error("insert_temperature failed");
    }
}

void IoTMySQL::update_location(double lat, double lng)
{
    std::stringstream ss;
    ss << "INSERT INTO location (device_id, lat, lng) VALUES (1, " << lat << ", " << lng << ");";
    //_cursor->execute(ss.str().c_str());
    if(!_cursor->execute(ss.str().c_str()))
    {
        throw std::runtime_error("update_location failed");
    }
}

