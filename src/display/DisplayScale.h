/**
 * @file DisplayScale.h
 *
 * @brief Display template with brew scale
 *
 */

#pragma once

#include "Display.h"

class DisplayScale : public Display {
    public:
        DisplayScale(Type displaytype) :
            Display(displaytype){};
        void printScreen(MachineState machineState, double temperature, double setpoint, unsigned int isrCounter, BrewSwitchState brewSwitchState) override;
};
