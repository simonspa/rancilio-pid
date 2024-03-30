/**
 * @file DisplayTemperature.h
 *
 * @brief Temp-only display template
 *
 */

#pragma once

#include "Display.h"

class DisplayTemperature : public Display {
    public:
        DisplayTemperature(Type displaytype) :
            Display(displaytype){};
        void printScreen(MachineState machineState, double temperature, double setpoint, unsigned int isrCounter, BrewSwitchState brewSwitchState) override;

    private:
        int blinkingtemp{1};           // 0: blinking near setpoint, 1: blinking far away from setpoint
        float blinkingtempoffset{0.3}; // offset for blinking
};
