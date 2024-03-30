#pragma once

enum MachineState {
    kInit = 0,
    kColdStart = 10,
    kAtSetpoint = 19,
    kPidNormal = 20,
    kBrew = 30,
    kShotTimerAfterBrew = 31,
    kBrewDetectionTrailing = 35,
    kSteam = 40,
    kCoolDown = 45,
    kBackflush = 50,
    kWaterEmpty = 70,
    kEmergencyStop = 80,
    kPidOffline = 90,
    kStandby = 95,
    kSensorError = 100,
    kEepromError = 110,
};

enum BrewSwitchState {
    kBrewSwitchIdle = 10,
    kBrewSwitchBrew = 20,
    kBrewSwitchBrewAbort = 30,
    kBrewSwitchFlushOff = 31,
    kBrewSwitchReset = 40
};

enum BrewState {
    kBrewIdle = 10,
    kPreinfusion = 20,
    kWaitPreinfusion = 21,
    kPreinfusionPause = 30,
    kWaitPreinfusionPause = 31,
    kBrewRunning = 40,
    kWaitBrew = 41,
    kBrewFinished = 42,
    kWaitBrewOff = 43
};

enum BackflushState {
    kBackflushWaitBrewswitchOn = 10,
    kBackflushFillingStart = 20,
    kBackflushFilling = 21,
    kBackflushFlushingStart = 30,
    kBackflushFlushing = 31,
    kBackflushWaitBrewswitchOff = 43
};
