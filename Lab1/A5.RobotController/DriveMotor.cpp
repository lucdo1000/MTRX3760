// DriveMotor.cpp
//
// Implementation file for the robot's drive motor.

#include "DriveMotor.h"
#include <iostream>

//---DriveMotor Implementation--------------------------------------
DriveMotor::DriveMotor()
    : mSpeed(0), mLastAccel(0), mLastBrake(0)
{
}

// The motor never decides for itself whether to drive or brake this
// cycle, that depends on the whole robot's speed, which is
// RegenerativeBraking's job. It calls Accelerate() or Brake() on us
// directly instead, exactly one of the two per cycle.
void DriveMotor::Run()
{
}

void DriveMotor::Report()
{
    std::cout << "DriveMotor: speed " << mSpeed;

    // only one of these is ever nonzero, so this always names what
    // actually happened to the motor this cycle
    if(mLastAccel > 0)
        std::cout << " (+" << mLastAccel << " accel)";
    else if(mLastBrake > 0)
        std::cout << " (-" << mLastBrake << " braked)";

    std::cout << std::endl;
}

void DriveMotor::Accelerate()
{
    int before = mSpeed;

    mSpeed += kAccel;
    if(mSpeed > kMaxSpeed) mSpeed = kMaxSpeed;

    // the real change, not just kAccel, in case the cap above clipped it
    mLastAccel = mSpeed - before;
    mLastBrake = 0;
}

void DriveMotor::Brake(int amount)
{
    int before = mSpeed;

    mSpeed -= amount;
    if(mSpeed < 0) mSpeed = 0;

    // same idea as Accelerate(), the real drop after clamping. This is
    // what RegenerativeBraking hands to the battery as the regen amount.
    mLastBrake = before - mSpeed;
    mLastAccel = 0;
}

int DriveMotor::GetSpeed() const
{
    return mSpeed;
}
