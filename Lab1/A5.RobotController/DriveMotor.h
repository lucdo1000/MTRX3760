// DriveMotor.h
//
// Header file for the robot's drive motor.

#ifndef DRIVEMOTOR_H
#define DRIVEMOTOR_H

#include "ISubsystem.h"
#include <iostream>

//---------------------------------------------------------------
// Models the robot's propulsion. A DriveMotor only knows its own speed —
// it has no idea RegenerativeBraking or BatteryMonitor exist. It doesn't
// decide for itself whether to speed up or slow down each cycle; that
// decision needs the whole robot's current speed, which is
// RegenerativeBraking's job (see RegenerativeBraking.h). So Run() here
// does nothing, and Accelerate()/Brake() are called on us directly by
// whichever subsystem is coordinating the cycle.
class DriveMotor : public ISubsystem
{
public:
    DriveMotor();

    void Run() override;
    void Report() override;

    // Speed up under the robot's own power. Called by RegenerativeBraking
    // when this is a drive cycle.
    void Accelerate();

    // Slow down under braking, by at most amount (never below 0). Called
    // by RegenerativeBraking when this is a braking cycle. Never called
    // in the same cycle as Accelerate().
    void Brake(int amount);

    int GetSpeed() const;

private:
    static const int kMaxSpeed = 30;   // speed cap, so acceleration can't run away forever
    static const int kAccel = 5;       // speed gained per Accelerate() call

    int mSpeed;
    int mLastAccel;   // this cycle's Accelerate() delta, for reporting (0 if braking)
    int mLastBrake;   // this cycle's Brake() delta, for reporting (0 if accelerating)
};

#endif