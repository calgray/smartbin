
#include "tbeam/axp192.h"

Axp192::Axp192()
{
    Wire.begin(SDA, SCL);
    _axp.setPowerOutPut(AXP192_DCDC1, AXP202_OFF); // OLED
    _axp.setPowerOutPut(AXP192_DCDC2, AXP202_OFF); // None
    _axp.setPowerOutPut(AXP192_DCDC2, AXP202_OFF); // 3.3V Pin, pin7, pin11
    _axp.setPowerOutPut(AXP192_LDO2, AXP202_OFF); // LoRa
    _axp.setPowerOutPut(AXP192_LDO3, AXP202_ON); // GPS
}

Axp192::~Axp192()
{
    _axp.setPowerOutPut(AXP192_DCDC1, AXP202_OFF); // OLED
    _axp.setPowerOutPut(AXP192_DCDC2, AXP202_OFF); // None
    _axp.setPowerOutPut(AXP192_DCDC2, AXP202_OFF); // 3.3V Pin, pin7, pin11
    _axp.setPowerOutPut(AXP192_LDO2, AXP202_OFF); // LoRa
    _axp.setPowerOutPut(AXP192_LDO3, AXP202_OFF); // GPS
}
