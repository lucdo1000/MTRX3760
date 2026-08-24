#include "RegenerativeBraking.h"

RegenerativeBraking::RegenerativeBraking(DriveMotor* motor, BatteryMonitor* battery)
    : mMotor(motor), mBattery(battery), mActive(false)
{
}

void RegenerativeBraking::Run()
{
    mActive = !mActive;

    // Tell motor whether brakes are active
    mMotor->Run(mActive);

    if(mActive)
    {
        int oldSpeed = mMotor->GetSpeed();

        mMotor->ReduceSpeed(10);   // braking amount

        int newSpeed = mMotor->GetSpeed();
        int speedDrop = oldSpeed - newSpeed;

        mBattery->RegenCharge(speedDrop);
    }
    else
    {
        mBattery->ProgressiveDrain(mMotor->GetSpeed());
    }
}



void RegenerativeBraking::Report()
{
    std::cout << "Regenerative braking: "
              << (mActive ? "ACTIVE" : "inactive")
              << std::endl;
}
