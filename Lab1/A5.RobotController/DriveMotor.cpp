#include "DriveMotor.h"

DriveMotor::DriveMotor()
    : mSpeed(0)
{
}

void DriveMotor::Run()
{
    mSpeed += 10;   // motor speeds up each cycle
}

void DriveMotor::Report()
{
    std::cout << "DriveMotor speed: " << mSpeed << std::endl;
}

void DriveMotor::ReduceSpeed(int amount)
{
    mSpeed -= amount;
    if(mSpeed < 0) mSpeed = 0;
}
