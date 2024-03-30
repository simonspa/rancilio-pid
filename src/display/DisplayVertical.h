/**
 * @file DisplayVertical.h
 *
 * @brief Class for vertically oriented displays
 */

#pragma once

#include "Display.h"

class DisplayVertical : public Display {
    public:
        DisplayVertical(Type displaytype) :
            Display(displaytype){};

        void displayLogo(String text1, String text2) override;

        void displayShottimer(MachineState state, BrewSwitchState brewSwitchState) override;

        void displayMachineState(MachineState state, double temperature, double setpoint, unsigned int isrCounter, BrewSwitchState brewSwitchState) override {
            // Vertical display does not show machine state
        }

        void printScreen(MachineState machineState, double temperature, double setpoint, unsigned int isrCounter, BrewSwitchState brewSwitchState) override;

    private:
        void prepare() override;

        bool display_enabled{false};
        uint8_t oled_i2c{OLED_I2C};
        U8G2 u8g2;
};
