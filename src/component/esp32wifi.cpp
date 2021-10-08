
#include "esp32wifi.h"
#include <WiFi.h>
#include "esp_wpa2.h"

Esp32WiFi::Esp32WiFi(const char* ssid, const char* password, int timeout_s)
{
    WiFi.begin(ssid, password);
    
    Serial.println("Connecting");
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < timeout_s) {
        retries++;
        delay(1000);
        Serial.print(".");
    }
    if(WiFi.status() == WL_CONNECTED)
    {
        Serial.println();
        Serial.print("Connected, IP address: ");
        Serial.println(WiFi.localIP());
    }
}

Esp32WiFi::Esp32WiFi(const char* ssid, const char* id, const char* username, const char* password)
{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)username, strlen(username));
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)username, strlen(username));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password, strlen(password));
    esp_wpa2_config_t wifi_config = WPA2_CONFIG_INIT_DEFAULT();
    esp_wifi_sta_wpa2_ent_enable(&wifi_config);
    WiFi.begin(ssid);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
}

Esp32WiFi::~Esp32WiFi()
{
    WiFi.disconnect(true);
}

bool Esp32WiFi::is_connected() const
{
    return WiFi.status() == WL_CONNECTED;
}

Client& Esp32WiFi::get_client()
{
    return (Client&)_client;
}