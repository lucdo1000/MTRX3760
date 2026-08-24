// BatteryMonitor.h
//
// Header file for the robot's battery.

#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include "ISubsystem.h"

//---BatteryMonitor Interface---------------------------------------
// Tracks the robot's battery percentage. Like DriveMotor, a
// BatteryMonitor doesn't know what caused a change in its own level,
// it just exposes Drain()/Charge() and applies whichever one is called.
// RegenerativeBraking is the only thing that calls them, once per
// cycle, once it has decided whether this is a drive or a braking cycle.
class BatteryMonitor : public ISubsystem
{
public:
    BatteryMonitor();

    void Run() override;
    void Report() override;

    // higher speed means more drain;
    // called by RegenerativeBraking on a drive cycle
    void Drain(int motorSpeed);

    // bigger speed drop means more charge;
    // called by RegenerativeBraking on a braking cycle
    void Charge(int speedDrop);

private:
    int mLevel;   // battery percentage, kept between 0 and 100

    // last Drain()/Charge() amount, for Report(). Only one of the two
    // is ever nonzero, since only one of them runs in a given cycle.
    int mLastDrain;
    int mLastCharge;
};

#endif
