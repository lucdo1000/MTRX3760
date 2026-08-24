// RegenerativeBraking.cpp
//
// Implementation file for the robot's regenerative braking system.

#include "RegenerativeBraking.h"
#include <iostream>

// Constructor
RegenerativeBraking::RegenerativeBraking(DriveMotor* motor, BatteryMonitor* battery)
    : mMotor(motor), mBattery(battery), mActive(false)
{
}

void RegenerativeBraking::Run()
{
    int speed = mMotor->GetSpeed();

    // decide whether braking should be active this cycle, based on the actual motor speed 
    if(!mActive && speed >= kEngageSpeed)
        mActive = true;
    else if(mActive && speed <= kDisengageSpeed)
        mActive = false;

    // robot will always either gets battery drained or recharged, one at a time
    if(mActive)
    {
        mMotor->Brake(kBrakeStrength);
        int speedDrop = speed - mMotor->GetSpeed();   // actual drop, after clamping

        mBattery->Charge(speedDrop);
    }
    else
    {
        mMotor->Accelerate();

        // speed after accelerating so drain reflects how fast the robot is going this cycle rather than last cycle
        mBattery->Drain(mMotor->GetSpeed());
    }
}

void RegenerativeBraking::Report()
{
    std::cout << "Regenerative braking: "
              << (mActive ? "ACTIVE" : "inactive")
              << std::endl;
}
