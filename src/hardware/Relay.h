/**
 * @file Relay.h
 * 
 * @brief A relay connected to a GPIO pin
 */
#pragma once

class GPIOPin;

class Relay {
    public:

        enum TriggerType {
            LOW_TRIGGER,
            HIGH_TRIGGER
        };

        Relay(GPIOPin& gpioInstance, TriggerType trigger = HIGH_TRIGGER);

        void on();
        void off();
        GPIOPin& getGPIOInstance();

    private:
        GPIOPin& gpio;
        TriggerType relayTrigger;
};
