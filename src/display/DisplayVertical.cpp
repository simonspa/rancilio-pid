/**
 * @file DisplayVertical.cpp
 *
 * @brief Vertical display class implementation
 */

#include "DisplayVertical.h"

void DisplayVertical::prepare() {
    if (!display_enabled) {
        return;
    }

    u8g2.setFont(u8g2_font_profont11_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    u8g2.setDisplayRotation(U8G2_R1); // fix setting for vertical
}

void DisplayVertical::displayLogo(String text1, String text2) {
    if (!display_enabled) {
        return;
    }

    u8g2.clearBuffer();
    u8g2.drawStr(0, 47, text1.c_str());
    u8g2.drawStr(0, 55, text2.c_str());

    u8g2.drawXBMP(11, 4, CleverCoffee_Logo_width, CleverCoffee_Logo_height, CleverCoffee_Logo);

    u8g2.sendBuffer();
}

void DisplayVertical::displayShottimer(MachineState, BrewSwitchState) {
    if (!display_enabled || FEATURE_SHOTTIMER == 0) {
        return;
    }

    if (((timeBrewed > 0 && BREWCONTROL_TYPE == 0) || (BREWCONTROL_TYPE > 0 && currBrewState > kBrewIdle && currBrewState <= kBrewFinished)) && FEATURE_SHOTTIMER == 1 && SHOTTIMER_TYPE == 1) {
        u8g2.clearBuffer();

        // draw temp icon
        u8g2.drawXBMP(0, 0, Brew_Cup_Logo_width, Brew_Cup_Logo_height, Brew_Cup_Logo);
        u8g2.setFont(u8g2_font_profont22_tf);
        u8g2.setCursor(5, 70);
        u8g2.print(timeBrewed / 1000, 1);
        u8g2.setFont(u8g2_font_profont11_tf);
        u8g2.sendBuffer();
    }

    if (FEATURE_SHOTTIMER == 1 && SHOTTIMER_TYPE == 1 && millis() >= lastBrewTimeMillis && // directly after creating lastbrewTimeMillis (happens when turning off the brew switch, case 43 in the code) should be started
        lastBrewTimeMillis + SHOTTIMERDISPLAYDELAY >= millis() &&                          // should run until millis() has caught up with SHOTTIMERDISPLAYDELAY, this can be used to control the display duration
        lastBrewTimeMillis < totalBrewTime) // if the totalBrewTime is reached automatically, nothing should be done, otherwise wrong time will be displayed because switch is pressed later than totalBrewTime
    {
        u8g2.clearBuffer();
        u8g2.drawXBMP(0, 0, Brew_Cup_Logo_width, Brew_Cup_Logo_height, Brew_Cup_Logo);
        u8g2.setFont(u8g2_font_profont22_tf);
        u8g2.setCursor(5, 70);
        u8g2.print((lastBrewTimeMillis - startingTime) / 1000, 1);
        u8g2.setFont(u8g2_font_profont11_tf);
        u8g2.sendBuffer();
    }
}

void DisplayVertical::printScreen(MachineState machineState, double temperature, double setpoint, unsigned int isrCounter, BrewSwitchState brewSwitchState) {
    if (!display_enabled) {
        return;
    }

    if (((machineState == kAtSetpoint || machineState == kPidNormal || machineState == kBrewDetectionTrailing) ||
         ((machineState == kBrew || machineState == kShotTimerAfterBrew) && FEATURE_SHOTTIMER == 0) || // shottimer == 0, auch Bezug anzeigen
         machineState == kCoolDown || ((machineState == kInit || machineState == kColdStart) && FEATURE_HEATINGLOGO == 0) || ((machineState == kPidOffline) && FEATURE_OFFLINELOGO == 0)) &&
        (brewSwitchState != kBrewSwitchFlushOff)) {
        if (machineState != kSensorError) {
            u8g2.clearBuffer();
            u8g2.setCursor(1, 14);
            u8g2.print(langstring_current_temp_rot_ur);
            u8g2.print(temperature, 1);
            u8g2.print(" ");
            u8g2.print((char)176);
            u8g2.print("C");
            u8g2.setCursor(1, 24);
            u8g2.print(langstring_set_temp_rot_ur);
            u8g2.print(setpoint, 1);
            u8g2.print(" ");
            u8g2.print((char)176);
            u8g2.print("C");

            // Draw heat bar
            u8g2.drawLine(0, 124, 63, 124);
            u8g2.drawLine(0, 124, 0, 127);
            u8g2.drawLine(64, 124, 63, 127);
            u8g2.drawLine(0, 127, 63, 127);
            u8g2.drawLine(1, 125, (pidOutput / 16.13) + 1, 125);
            u8g2.drawLine(1, 126, (pidOutput / 16.13) + 1, 126);

            // print heating status
            u8g2.setCursor(1, 50);
            u8g2.setFont(u8g2_font_profont22_tf);

            if (fabs(temperature - setpoint) < 0.3) {
                if (isrCounter < 500) {
                    u8g2.print("OK");
                }
            }
            else {
                u8g2.print("WAIT");
            }

            u8g2.setFont(u8g2_font_profont11_tf);

            if (isBrewDetected == 1) {
                u8g2.setCursor(1, 75);
                u8g2.print("BD ");
                u8g2.print((millis() - timeBrewDetection) / 1000, 1);
                u8g2.print("/");
                u8g2.print(brewtimesoftware, 0);
            }

            // PID values above heater output bar
            u8g2.setCursor(1, 84);
            u8g2.print("P: ");
            u8g2.print(bPID.GetKp(), 0);

            u8g2.setCursor(1, 93);
            u8g2.print("I: ");

            if (bPID.GetKi() != 0) {
                u8g2.print(bPID.GetKp() / bPID.GetKi(), 0);
            }
            else {
                u8g2.print("0");
            }

            u8g2.setCursor(1, 102);
            u8g2.print("D: ");
            u8g2.print(bPID.GetKd() / bPID.GetKp(), 0);

            u8g2.setCursor(1, 111);

            if (pidOutput < 99) {
                u8g2.print(pidOutput / 10, 1);
            }
            else {
                u8g2.print(pidOutput / 10, 0);
            }

            u8g2.print("%");

            // Brew
            u8g2.setCursor(1, 34);
            u8g2.print(langstring_brew_rot_ur);
            u8g2.print(timeBrewed / 1000, 0);
            u8g2.print("/");

            if (BREWCONTROL_TYPE == 0) {
                u8g2.print(brewtimesoftware, 0);     // deaktivieren wenn Preinfusion ( // voransetzen )
            }
            else {
                u8g2.print(totalBrewTime / 1000, 0); // aktivieren wenn Preinfusion
            }

            u8g2.print(" s");

            // For status info
            u8g2.drawFrame(0, 0, 64, 12);

            if (offlineMode == 0) {

                if (WiFi.status() == WL_CONNECTED) {
                    u8g2.drawXBMP(4, 2, 8, 8, Antenna_OK_Icon);

                    for (int b = 0; b <= getSignalStrength(); b++) {
                        u8g2.drawVLine(13 + (b * 2), 10 - (b * 2), b * 2);
                    }
                }
                else {
                    u8g2.drawXBMP(4, 2, 8, 8, Antenna_NOK_Icon);
                    u8g2.setCursor(56, 2);
                    u8g2.print("RC: ");
                    u8g2.print(wifiReconnects);
                }

                if (FEATURE_MQTT == 1) {
                    if (mqtt.connected() == 1) {
                        u8g2.setCursor(24, 2);
                        u8g2.setFont(u8g2_font_profont11_tf);
                        u8g2.print("MQTT");
                    }
                    else {
                        u8g2.setCursor(24, 2);
                        u8g2.print("");
                    }
                }
            }
            else {
                u8g2.setCursor(4, 1);
                u8g2.print("Offline");
            }

            u8g2.sendBuffer();
        }
    }
}
