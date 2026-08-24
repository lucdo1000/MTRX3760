#include "DriveMotor.h"

DriveMotor::DriveMotor()
    : mSpeed(0), mLastSpeed(0)
{
}

void DriveMotor::Run()
{
    mLastSpeed = mSpeed;
    mSpeed += 20;   // motor speeds up each cycle
}

void DriveMotor::Report()
{
    std::cout << "DriveMotor speed: " << mSpeed << std::endl;
}

void DriveMotor::ReduceSpeed(int amount)
{
    mLastSpeed = mSpeed;
    mSpeed -= amount;
    if(mSpeed < 0) mSpeed = 0;
}

int DriveMotor::GetSpeed() const
{
    return mSpeed;
}

int DriveMotor:: GetLastSpeed() const 
{
    return mLastSpeed;
}
