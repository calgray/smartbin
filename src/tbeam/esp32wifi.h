#include <WiFi.h>

class Esp32WiFi
{
    WiFiClient _client;
public:
    Esp32WiFi(const char* ssid, const char* password);
    Esp32WiFi(const char* ssid, const char* id, const char* username, const char* password);
    ~Esp32WiFi();
    Client& get_client();
};