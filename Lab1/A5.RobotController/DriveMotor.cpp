#include "DriveMotor.h"

DriveMotor::DriveMotor()
    : mSpeed(0), mLastSpeed(0)
{
}

void DriveMotor::Run(bool brakesActive)
{
    mLastSpeed = mSpeed;

    if(brakesActive)
        return;   // no acceleration allowed

    mSpeed += 10;
}


void DriveMotor::Report()
{
    std::cout << "DriveMotor speed: " << mSpeed << std::endl;
}

void DriveMotor::ReduceSpeed(int amount)
{
    mLastSpeed = mSpeed;

    if(amount > mSpeed)
        amount = mSpeed;   // cap reduction to current speed

    mSpeed -= amount;
}


int DriveMotor::GetSpeed() const
{
    return mSpeed;
}

int DriveMotor::GetLastSpeed() const 
{
    return mLastSpeed;
}
