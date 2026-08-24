// RegenerativeBraking.cpp
//
// Implementation file for the robot's regenerative braking system.
//
// DriveMotor and BatteryMonitor are deliberately "dumb": they hold state
// and expose intention-revealing methods (Accelerate/Brake, Drain/Charge)
// but never decide when to call them on themselves. Something has to make
// that call each cycle, and it has to be based on the motor's speed — so
// it lives here, the one subsystem that already needs a DriveMotor* and a
// BatteryMonitor* to do its own job.

#include "RegenerativeBraking.h"

//---------------------------------------------------------------
RegenerativeBraking::RegenerativeBraking(DriveMotor* motor, BatteryMonitor* battery)
    : mMotor(motor), mBattery(battery), mActive(false)
{
}

//---------------------------------------------------------------
void RegenerativeBraking::Run()
{
    int speed = mMotor->GetSpeed();

    // Decide whether braking should be active this cycle, based on
    // actual motor speed rather than an unconditional toggle.
    if(!mActive && speed >= kEngageSpeed)
        mActive = true;
    else if(mActive && speed <= kDisengageSpeed)
        mActive = false;

    // Exactly one of drive or brake happens this cycle, never both — so
    // exactly one of drain or charge happens too, caused by whichever
    // subsystem actually did something.
    if(mActive)
    {
        mMotor->Brake(kBrakeStrength);
        int speedDrop = speed - mMotor->GetSpeed();   // actual drop, after any clamping

        mBattery->Charge(speedDrop);
    }
    else
    {
        mMotor->Accelerate();

        // Use the motor's speed after accelerating (not before), so drain
        // reflects how fast the robot is going this cycle, not last cycle.
        mBattery->Drain(mMotor->GetSpeed());
    }
}

//---------------------------------------------------------------
void RegenerativeBraking::Report()
{
    std::cout << "Regenerative braking: "
              << (mActive ? "ACTIVE" : "inactive")
              << std::endl;
}