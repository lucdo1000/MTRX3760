#ifndef REGENERATIVEBRAKING_H
#define REGENERATIVEBRAKING_H

#include "ISubsystem.h"
#include "DriveMotor.h"
#include "BatteryMonitor.h"
#include <iostream>

class RegenerativeBraking : public ISubsystem
{
public:
    RegenerativeBraking(DriveMotor* motor, BatteryMonitor* battery);

    void Run() override;
    void Report() override;

private:
    DriveMotor* mMotor;
    BatteryMonitor* mBattery;
    bool mActive;
};

#endif
