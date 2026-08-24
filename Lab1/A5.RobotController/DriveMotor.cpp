#include "DriveMotor.h"

DriveMotor::DriveMotor()
    : mSpeed(0), mLastAccel(0), mLastBrake(0)
{
}

void DriveMotor::Run()
{
    // The motor never decides for itself whether to drive or brake this
    // cycle — that call depends on the whole robot's current speed, which
    // is RegenerativeBraking's job. It calls Accelerate() or Brake() on
    // us directly, exactly one of the two per cycle.
}

void DriveMotor::Report()
{
    std::cout << "DriveMotor: speed " << mSpeed;
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

    mLastAccel = mSpeed - before;
    mLastBrake = 0;
}

void DriveMotor::Brake(int amount)
{
    int before = mSpeed;

    mSpeed -= amount;
    if(mSpeed < 0) mSpeed = 0;

    mLastBrake = before - mSpeed;
    mLastAccel = 0;
}

int DriveMotor::GetSpeed() const
{
    return mSpeed;
}