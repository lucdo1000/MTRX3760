#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include "ISubsystem.h"
#include <iostream>

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
    int mLevel;        // battery percentage
    int mLastDrain;    // this cycle's drain, for reporting (0 if none)
    int mLastCharge;   // this cycle's regen charge, for reporting (0 if none)
};

#endif