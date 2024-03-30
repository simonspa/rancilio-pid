/**
 * @file DisplayStandard.h
 *
 * @brief Standard display template
 *
 */

#pragma once

#include "Display.h"

class DisplayStandard : public Display {
    public:
        DisplayStandard(Type displaytype) :
            Display(displaytype){};
        void printScreen(MachineState machineState, double temperature, double setpoint, unsigned int isrCounter, BrewSwitchState brewSwitchState) override;
};
