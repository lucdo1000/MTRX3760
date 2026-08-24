#ifndef REGENERATIVEBRAKING_H
#define REGENERATIVEBRAKING_H

#include "ISubsystem.h"
#include "DriveMotor.h"
#include "BatteryMonitor.h"
#include <iostream>

// Decides, every cycle, whether the robot drives or brakes — it's the only
// subsystem that reads the motor's speed, so it's the natural place for
// that call to live. On a drive cycle it tells the motor to accelerate and
// the battery to drain; on a braking cycle it tells the motor to brake and
// the battery to charge. Never both in the same cycle.
class RegenerativeBraking : public ISubsystem
{
public:
    RegenerativeBraking(DriveMotor* motor, BatteryMonitor* battery);

    void Run() override;
    void Report() override;

private:
    // Hysteresis thresholds: brake once speed reaches kEngageSpeed, keep
    // braking until speed falls back to kDisengageSpeed. Avoids flickering
    // on/off right at a single boundary value.
    //
    // Because drive and brake are mutually exclusive, speed can only ever
    // fall while braking (nothing is accelerating it at the same time), so
    // it's guaranteed to reach kDisengageSpeed eventually regardless of how
    // kBrakeStrength is tuned — this can't lock into a permanent brake the
    // way it could if accelerating and braking both applied in one cycle.
    static const int kEngageSpeed = 15;
    static const int kDisengageSpeed = 5;
    static const int kBrakeStrength = 10;

    DriveMotor* mMotor;
    BatteryMonitor* mBattery;
    bool mActive;
};

#endif