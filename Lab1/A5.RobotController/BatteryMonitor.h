// BatteryMonitor.h
//
// Header file for the robot's battery.

#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include "ISubsystem.h"
#include <iostream>

//---------------------------------------------------------------
// Tracks the robot's battery percentage. Like DriveMotor, a
// BatteryMonitor has no idea what caused a change in its own level — it
// just exposes Drain()/Charge() and applies whichever one is called.
// RegenerativeBraking is the only thing that calls them, once per cycle,
// after it has decided whether this is a drive cycle or a braking cycle.
class BatteryMonitor : public ISubsystem
{
public:
    BatteryMonitor();

    void Run() override;
    void Report() override;

    // Called by RegenerativeBraking on a drive cycle. Higher speed = more drain.
    void Drain(int motorSpeed);

    // Called by RegenerativeBraking on a braking cycle. Bigger speed drop = more charge.
    void Charge(int speedDrop);

private:
    int mLevel;        // battery percentage, clamped to [0, 100]
    int mLastDrain;    // this cycle's drain, for reporting (0 if none)
    int mLastCharge;   // this cycle's regen charge, for reporting (0 if none)
};

#endif