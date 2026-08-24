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
