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

    // For regenerative breaking
    void Charge(int amount);

    // Higher speed = Higher battery drain
    void ProgressiveDrain(int motorSpeed);
    void RegenCharge(int speedDrop);

private:
    int mLevel;   // battery percentage
};

#endif
