// RegenerativeBraking.cpp
//
// Implementation file for the robot's regenerative braking system.
//
// DriveMotor and BatteryMonitor just hold state and expose methods to
// change it, Accelerate/Brake, Drain/Charge, but never call those
// methods on themselves. Something has to decide when to, each cycle,
// and that decision needs the motor's speed. So it lives here, the one
// subsystem that already needs a DriveMotor* and a BatteryMonitor* to
// do its own job.

#include "RegenerativeBraking.h"
#include <iostream>

//---RegenerativeBraking Implementation--------------------------------
RegenerativeBraking::RegenerativeBraking(DriveMotor* motor, BatteryMonitor* battery)
    : mMotor(motor), mBattery(battery), mActive(false)
{
}

void RegenerativeBraking::Run()
{
    int speed = mMotor->GetSpeed();

    // decide whether braking should be active this cycle, based on the
    // actual motor speed rather than an unconditional toggle
    if(!mActive && speed >= kEngageSpeed)
        mActive = true;
    else if(mActive && speed <= kDisengageSpeed)
        mActive = false;

    // exactly one of drive or brake happens this cycle, never both, so
    // exactly one of drain or charge happens too, caused by whichever
    // subsystem actually did something
    if(mActive)
    {
        mMotor->Brake(kBrakeStrength);
        int speedDrop = speed - mMotor->GetSpeed();   // actual drop, after clamping

        mBattery->Charge(speedDrop);
    }
    else
    {
        mMotor->Accelerate();

        // speed after accelerating, not before, so drain reflects how
        // fast the robot is going this cycle rather than last cycle
        mBattery->Drain(mMotor->GetSpeed());
    }
}

void RegenerativeBraking::Report()
{
    std::cout << "Regenerative braking: "
              << (mActive ? "ACTIVE" : "inactive")
              << std::endl;
}
