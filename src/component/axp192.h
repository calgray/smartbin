#pragma once

#include <axp20x.h>
#include <optional>

class Axp192
{
    AXP20X_Class _axp;
public:
    Axp192();
    ~Axp192();

    AXP20X_Class& getimpl() { return _axp; }
    std::optional<double> get_battery_voltage()
    {
        std::optional<double> v;
        double vmAh = _axp.getBattVoltage();
        if (vmAh == AXP_NOT_INIT)
        {
            v = vmAh / 1000.0f;
        }
        return v;
    }

};
