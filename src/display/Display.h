/**
 * @file Display.h
 *
 * @brief Base class for OLED Displays
 */

#pragma once

#include <SPI.h>
#include <U8g2lib.h> // i2c display

#include <WiFi.h>

#include "display/bitmaps.h" // user icons for display
#include "languages.h"
#include "machinestates.h"

/**
 * @class Base class for OLED Displays
 */
class Display {
    public:
        enum Type {
            NONE,
            SH1106,
            SSD1306,
            SH1106_126x64_SPI,
        };

        Display(Type displaytype);

        void setPowerSave(bool enable);

        /**
         * @brief print logo and message at boot
         */
        virtual void displayLogo(String text1, String text2);

        /**
         * @brief display shot timer
         */
        virtual void displayShottimer(MachineState state, BrewSwitchState brewSwitchState);

        virtual void printScreen(MachineState machineState, double temperature, double setpoint, unsigned int isrCounter, BrewSwitchState brewSwitchState) = 0;
        /**
         * @brief print message
         */
        void displayMessage(String text1, String text2, String text3, String text4, String text5, String text6);

        /**
         * @brief display heating logo
         */
        virtual void displayMachineState(MachineState state, double temperature, double setpoint, unsigned int isrCounter, BrewSwitchState brewSwitchState);

        void enableOfflineMode() {
            offlineMode = true;
        }

    protected:
        /**
         * @brief initialize display
         */
        virtual void prepare();

        bool display_enabled{false};
        uint8_t oled_i2c{OLED_I2C};
        U8G2 u8g2;

        bool offlineMode{false};

        /**
         * @brief Get Wifi signal strength and set signalBars for display
         */
        int getSignalStrength();

        void displayStatusbar();
        void displayProgressbar(int value, int x, int y, int width);
        void displayBrewtime(int x, int y, double brewtime);
        void displayTemperature(int x, int y);
        void drawTemperaturebar(int x, int y, int heightRange, double temperature);
        void displayThermometerOutline(int x, int y);
        void displayMQTTStatus(int x, int y);
        void displayWiFiStatus(int x, int y);
        void displayUptime(int x, int y, const char* format);
        void displayWaterIcon(int x, int y);
};
