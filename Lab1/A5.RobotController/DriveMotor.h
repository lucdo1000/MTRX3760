#ifndef DRIVEMOTOR_H
#define DRIVEMOTOR_H

#include "ISubsystem.h"
#include <iostream>

class DriveMotor : public ISubsystem
{
public:
    DriveMotor();

    void Run() override;
    void Report() override;

    // Speed up under the robot's own power. Called by RegenerativeBraking
    // when this is a drive cycle.
    void Accelerate();

    // Slow down under braking. Called by RegenerativeBraking when this
    // is a braking cycle. Never called in the same cycle as Accelerate().
    void Brake(int amount);

    int GetSpeed() const;

private:
    static const int kMaxSpeed = 30;
    static const int kAccel = 5;

    int mSpeed;
    int mLastAccel;   // this cycle's Accelerate() delta, for reporting (0 if braking)
    int mLastBrake;   // this cycle's Brake() delta, for reporting (0 if accelerating)
};

#endif