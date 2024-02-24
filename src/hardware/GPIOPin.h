/**
 * @file GPIOPin.h
 * 
 * @brief Abstraction of a GPIO pin 
 */

#pragma once

#include <Arduino.h>

class GPIOPin {
    public:

        enum Type {
            OUT,
            IN_STANDARD,
            IN_PULLUP,      // Internal pull-up resistor
            IN_PULLDOWN,    // Internal pull-down resistor
            IN_HARDWARE,    // External pull-up/pull-down resistor
            IN_ANALOG
        };

        GPIOPin(int pinNumber, Type pinType);

        void write(bool value) const;
        void setType(Type pinType);
        int read() const;
        Type getType() const;

    private:
        int pin;
        Type pinType;
};

