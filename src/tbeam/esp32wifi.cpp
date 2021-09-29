
#include "esp32wifi.h"
#include "esp_wpa2.h"
#include <WiFi.h>

Esp32WiFi::Esp32WiFi(const char* ssid, const char* password)
{
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
}

Esp32WiFi::Esp32WiFi(const char* ssid, const char* username, const char* password)
{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)ssid, strlen(ssid));
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)username, strlen(username));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password, strlen(password));
    esp_wpa2_config_t wifi_config = WPA2_CONFIG_INIT_DEFAULT();
    esp_wifi_sta_wpa2_ent_enable(&wifi_config);
    WiFi.begin(ssid, password);
}

Esp32WiFi::~Esp32WiFi()
{
    WiFi.disconnect(true);
}

Client& Esp32WiFi::get_client()
{
    return (Client&)_client;
}