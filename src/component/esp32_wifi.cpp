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

#include "esp32_wifi.h"
#include <WiFi.h>
#include <esp_wpa2.h>
#include <esp_wifi.h>
#include <stream_extensions.h>

Esp32WiFi::Esp32WiFi(const char* ssid, const char* password, int timeout_s)
{
    WiFi.begin(ssid, password);
    
    Serial << "Connecting";
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < timeout_s) {
        retries++;
        delay(1000);
        Serial << ".";
    }
    if(WiFi.status() == WL_CONNECTED)
    {
        Serial << "\nConnected, IP address: " << WiFi.localIP() << "\n";
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

    Serial << "Connecting";
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial << ".";
    }
    Serial << "\nConnected, IP address: " << WiFi.localIP() << "\n";
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
