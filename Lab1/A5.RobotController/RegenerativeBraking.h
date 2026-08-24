// RegenerativeBraking.h
//
// Header file for the robot's regenerative braking system. This is the
// only subsystem that talks to the other two directly, it holds a
// DriveMotor* and a BatteryMonitor*. See RegenerativeBraking.cpp for
// why that belongs here and not in DriveMotor or BatteryMonitor.

#ifndef REGENERATIVEBRAKING_H
#define REGENERATIVEBRAKING_H

#include "ISubsystem.h"
#include "DriveMotor.h"
#include "BatteryMonitor.h"

//---RegenerativeBraking Interface---------------------------------------
// Decides, every cycle, whether the robot drives or brakes. It's the
// only subsystem that reads the motor's speed, so that decision has to
// live here. On a drive cycle it tells the motor to accelerate and the
// battery to drain, on a braking cycle it tells the motor to brake and
// the battery to charge. Never both in the same cycle.
class RegenerativeBraking : public ISubsystem
{
public:
    // does not own motor or battery, just holds pointers to them.
    // main.cpp owns both and must keep them alive longer than this.
    RegenerativeBraking(DriveMotor* motor, BatteryMonitor* battery);

    void Run() override;
    void Report() override;

private:
    // hysteresis thresholds: brake once speed reaches kEngageSpeed, keep
    // braking until speed falls back to kDisengageSpeed. Using two
    // thresholds instead of one stops it flickering on and off right at
    // a single boundary.
    //
    // Drive and brake are mutually exclusive, so speed can only ever
    // fall while braking, nothing is accelerating it at the same time.
    // That means it's guaranteed to reach kDisengageSpeed eventually no
    // matter how kBrakeStrength is tuned, it can't lock into a permanent
    // brake the way it could if accelerating and braking both applied
    // in the same cycle.
    static const int kEngageSpeed = 15;
    static const int kDisengageSpeed = 5;
    static const int kBrakeStrength = 10;   // speed lost per Brake() call while active

    DriveMotor* mMotor;
    BatteryMonitor* mBattery;
    bool mActive;   // true while braking
};

#endif
