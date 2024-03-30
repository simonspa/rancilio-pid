/**
 * @file DisplayMinimal.h
 *
 * @brief Minimal display template
 *
 */

#pragma once

#include "Display.h"

class DisplayMinimal : public Display {
    public:
        DisplayMinimal(Type displaytype) :
            Display(displaytype){};
        void printScreen(MachineState machineState, double temperature, double setpoint, unsigned int isrCounter, BrewSwitchState brewSwitchState) override;
};
