#pragma once

#include <axp20x.h>
#include <optional>

class Axp192
{
    AXP20X_Class _axp;
public:
    Axp192();
    ~Axp192();
    std::optional<double> get_battery_voltage();
    AXP20X_Class& get_impl();
};
