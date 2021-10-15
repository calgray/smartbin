#pragma once

#include <WiFi.h>

class Esp32WiFi
{
    WiFiClient _client;
public:
    Esp32WiFi(const char* ssid, const char* password, int timeout_s = 10);
    Esp32WiFi(const char* ssid, const char* id, const char* username, const char* password);
    ~Esp32WiFi();

    bool is_connected() const;
    
    Client& get_client();
};