/**
 * MIT License
 * 
 * Copyright (c) 2021 UWA-CITS5506-Gp01
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
        Serial << "error: " << err << "\n";
    }
    
    // Block until dns future is joined
    IPAddress host_ip2 = future.get();

    Serial << "Connecting to db at " << host_ip2 << ":" << port << "\n";

    if(_db.connect(host_ip2, port, usr, pwd))
    {
        Serial << "Connection success!\n";
        _cursor = new MySQL_Cursor(&_db);
        _cursor->execute("USE smartbin;");
    }
    else
    {
        Serial << "Connection failed!";
    }
}

void IoTMySQL::dns_found(const char *name, const ip_addr_t *ipaddr, void *callback_arg)
{
    Serial << "dns resolved\n";
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

void IoTMySQL::register_device()
{
    constexpr char INSERT_DEVICE[] = "INSERT INTO devices VALUES (0, 'arduino-esp32', 1111);";
    if(!_cursor->execute(INSERT_DEVICE))
    {
        throw std::runtime_error("insert_device failed");
    }
}

void IoTMySQL::insert_record(
    std::optional<double> distance,
    std::optional<double> temp,
    std::optional<double> battery,
    std::optional<double> lat,
    std::optional<double> lng)
{
    std::stringstream ss;
    ss << "INSERT INTO records (device_id, distance, temperature, battery, lat, lng)";
    ss << " VALUES (1, " << distance << ", " << temp << ", " << battery << ", " << lat << ", " << lng << ");";
    if(!_cursor->execute(ss.str().c_str()))
    {
        throw std::runtime_error("insert_data failed");
    }
}
