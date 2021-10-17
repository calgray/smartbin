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

#include "component/axp192.h"

Axp192::Axp192()
{
    Wire.begin(SDA, SCL);
    _axp.begin(Wire, AXP192_SLAVE_ADDRESS);
    //_axp.setPowerOutPut(AXP192_DCDC1, AXP202_OFF); // OLED
    //_axp.setPowerOutPut(AXP192_DCDC2, AXP202_OFF); // None
    //_axp.setPowerOutPut(AXP192_DCDC3, AXP202_OFF); // 3.3V Pin, pin7, pin11
    _axp.setPowerOutPut(AXP192_LDO2, AXP202_OFF); // LoRa
    _axp.setPowerOutPut(AXP192_LDO3, AXP202_ON); // GPS
}

Axp192::~Axp192()
{
    //_axp.setPowerOutPut(AXP192_DCDC1, AXP202_OFF); // OLED
    //_axp.setPowerOutPut(AXP192_DCDC2, AXP202_OFF); // None
    //_axp.setPowerOutPut(AXP192_DCDC3, AXP202_OFF); // 3.3V Pin, pin7, pin11
    _axp.setPowerOutPut(AXP192_LDO2, AXP202_OFF); // LoRa
    _axp.setPowerOutPut(AXP192_LDO3, AXP202_OFF); // GPS
}
