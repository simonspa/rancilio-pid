/**
 * @file DisplayTemperature.cpp
 *
 * @brief Temp-only display template
 *
 */

#include "DisplayTemperature.h"

void DisplayTemperature::printScreen(MachineState machineState, double temperature, double setpoint, unsigned int isrCounter, BrewSwitchState brewSwitchState) {
    if (!display_enabled) {
        return;
    }

    if (((machineState == kAtSetpoint || machineState == kPidNormal || machineState == kBrewDetectionTrailing) ||
         ((machineState == kBrew || machineState == kShotTimerAfterBrew) && FEATURE_SHOTTIMER == 0) || // shottimer == 0, auch Bezug anzeigen
         machineState == kCoolDown || ((machineState == kInit || machineState == kColdStart) && FEATURE_HEATINGLOGO == 0) || ((machineState == kPidOffline) && FEATURE_OFFLINELOGO == 0)) &&
        (brewSwitchState != kBrewSwitchFlushOff)) {
        if (machineState != kSensorError) {
            u8g2.clearBuffer();

            // draw (blinking) temp
            if (((fabs(temperature - setpoint) < blinkingtempoffset && blinkingtemp == 0) || (fabs(temperature - setpoint) >= blinkingtempoffset && blinkingtemp == 1)) && !FEATURE_STATUS_LED) {
                if (isrCounter < 500) {
                    if (temperature < 99.999) {
                        u8g2.setCursor(8, 22);
                        u8g2.setFont(u8g2_font_fub35_tf);
                        u8g2.print(temperature, 1);
                        u8g2.drawCircle(116, 27, 4);
                    }
                    else {
                        u8g2.setCursor(24, 22);
                        u8g2.setFont(u8g2_font_fub35_tf);
                        u8g2.print(temperature, 0);
                        u8g2.drawCircle(116, 27, 4);
                    }
                }
            }
            else {
                if (temperature < 99.999) {
                    u8g2.setCursor(8, 22);
                    u8g2.setFont(u8g2_font_fub35_tf);
                    u8g2.print(temperature, 1);
                    u8g2.drawCircle(116, 27, 4);
                }
                else {
                    u8g2.setCursor(24, 22);
                    u8g2.setFont(u8g2_font_fub35_tf);
                    u8g2.print(temperature, 0);
                    u8g2.drawCircle(116, 27, 4);
                }
            }
        }

        displayStatusbar();

        u8g2.sendBuffer();
    }
}
