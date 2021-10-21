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

class RTC
{
    RTC();
    ~RTC();

    void print_wakeup_reason()
    {
        esp_sleep_wakeup_cause_t wakeup_reason;

        wakeup_reason = esp_sleep_get_wakeup_cause();

        switch(wakeup_reason)
        {
            case ESP_SLEEP_WAKEUP_EXT0:
                Serial << "Wakeup caused by external signal using RTC_IO\n";
                break;
            case ESP_SLEEP_WAKEUP_EXT1:
                Serial << "Wakeup caused by external signal using RTC_CNTL\n";
                break;
            case ESP_SLEEP_WAKEUP_TIMER:
                Serial << "Wakeup caused by timer\n";
                break;
            case ESP_SLEEP_WAKEUP_TOUCHPAD:
                Serial << "Wakeup caused by touchpad\n";
                break;
            case ESP_SLEEP_WAKEUP_ULP:
                Serial << "Wakeup caused by ULP program\n";
                break;
            default:
                Serial << "Wakeup was not caused by deep sleep:" << wakeup_reason << "\n";
                break;
        }
    }

    void sleep(int us)
    {
        esp_deep_sleep(us);
    }
};