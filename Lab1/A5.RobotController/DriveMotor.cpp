// DriveMotor.cpp
//
// Implementation file for the robot's drive motor.

#include "DriveMotor.h"

//---------------------------------------------------------------
DriveMotor::DriveMotor()
    : mSpeed(0), mLastAccel(0), mLastBrake(0)
{
}

//---------------------------------------------------------------
void DriveMotor::Run()
{
    // The motor never decides for itself whether to drive or brake this
    // cycle — that call depends on the whole robot's current speed, which
    // is RegenerativeBraking's job. It calls Accelerate() or Brake() on
    // us directly, exactly one of the two per cycle.
}

//---------------------------------------------------------------
void DriveMotor::Report()
{
    std::cout << "DriveMotor: speed " << mSpeed;
    // Only one of mLastAccel/mLastBrake is ever nonzero at once (see
    // Accelerate()/Brake() below), so this always describes exactly what
    // happened to the motor this cycle.
    if(mLastAccel > 0)
        std::cout << " (+" << mLastAccel << " accel)";
    else if(mLastBrake > 0)
        std::cout << " (-" << mLastBrake << " braked)";
    std::cout << std::endl;
}

//---------------------------------------------------------------
void DriveMotor::Accelerate()
{
    int before = mSpeed;

    mSpeed += kAccel;
    if(mSpeed > kMaxSpeed) mSpeed = kMaxSpeed;   // don't exceed the speed cap

    // Recover the actual change (not just kAccel) in case the cap above
    // clipped it, so the reported figure always matches what really
    // happened to mSpeed.
    mLastAccel = mSpeed - before;
    mLastBrake = 0;   // this cycle was a drive cycle, not a braking one
}

//---------------------------------------------------------------
void DriveMotor::Brake(int amount)
{
    int before = mSpeed;

    mSpeed -= amount;
    if(mSpeed < 0) mSpeed = 0;   // can't go below stationary

    // Same idea as Accelerate(): compute the real drop after clamping,
    // not the requested amount, so RegenerativeBraking gets an accurate
    // speedDrop to hand to the battery for the regen charge calculation.
    mLastBrake = before - mSpeed;
    mLastAccel = 0;   // this cycle was a braking cycle, not a drive one
}

//---------------------------------------------------------------
int DriveMotor::GetSpeed() const
{
    return mSpeed;
}