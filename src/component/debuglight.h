#pragma once

#include "tbeamv1.h"
#include "component/axp192.h"

class DebugLights
{
    Axp192 _axp;

public:
    DebugLights(Axp192& axp)
    : _axp(axp)
    {
        pinMode(ONBOARD_LED, OUTPUT);
        disable_error();
    }

    void enable_error()
    {
        _axp.getimpl().setChgLEDMode(axp_chgled_mode_t::AXP20X_LED_BLINK_1HZ);
        digitalWrite(ONBOARD_LED, LOW); // LOW is on
    }

    void disable_error()
    {
        _axp.getimpl().setChgLEDMode(axp_chgled_mode_t::AXP20X_LED_OFF);
        digitalWrite(ONBOARD_LED, HIGH); // HIGH is off
    }
};
