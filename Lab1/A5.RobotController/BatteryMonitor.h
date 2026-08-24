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

private:
    int mLevel;   // battery percentage
};

#endif
