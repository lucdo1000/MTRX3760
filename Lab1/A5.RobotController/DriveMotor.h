// DriveMotor.h
//
// Header file for the robot's drive motor.

#ifndef DRIVEMOTOR_H
#define DRIVEMOTOR_H

#include "ISubsystem.h"

//---DriveMotor Interface------------------------------------------
// Models the robot's propulsion. A DriveMotor only knows its own speed,
// it has no idea RegenerativeBraking or BatteryMonitor exist. Deciding
// whether to speed up or slow down needs the robot's current speed,
// and that decision belongs to RegenerativeBraking, so Run() here does
// nothing. Accelerate() and Brake() get called on us directly instead.
class DriveMotor : public ISubsystem
{
public:
    DriveMotor();

    void Run() override;
    void Report() override;

    // speed up under the robot's own power;
    // called by RegenerativeBraking on a drive cycle
    void Accelerate();

    // slow down under braking, by at most amount, never below 0;
    // called by RegenerativeBraking on a braking cycle
    void Brake(int amount);

    // current speed
    int GetSpeed() const;

private:
    static const int kMaxSpeed = 30;   // speed cap
    static const int kAccel = 5;       // speed gained per Accelerate() call

    int mSpeed;

    // last Accelerate()/Brake() amount, for Report(). Only one of the two
    // is ever nonzero, since only one of them runs in a given cycle.
    int mLastAccel;
    int mLastBrake;
};

#endif
