#include "RegenerativeBraking.h"

RegenerativeBraking::RegenerativeBraking(DriveMotor* motor, BatteryMonitor* battery)
    : mMotor(motor), mBattery(battery), mActive(false)
{
}

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
        int speedDrop = speed - mMotor->GetSpeed();

        mBattery->Charge(speedDrop);
    }
    else
    {
        mMotor->Accelerate();

        mBattery->Drain(mMotor->GetSpeed());
    }
}

void RegenerativeBraking::Report()
{
    std::cout << "Regenerative braking: "
              << (mActive ? "ACTIVE" : "inactive")
              << std::endl;
}