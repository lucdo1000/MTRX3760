#include "RegenerativeBraking.h"

RegenerativeBraking::RegenerativeBraking(DriveMotor* motor, BatteryMonitor* battery)
    : mMotor(motor), mBattery(battery), mActive(false)
{
}

void RegenerativeBraking::Run()
{
    mActive = !mActive;

    if(mActive)
    {
        int oldSpeed = mMotor->GetSpeed();

        // Apply braking
        mMotor->ReduceSpeed(10);

        int newSpeed = mMotor->GetSpeed();
        int speedDrop = oldSpeed - newSpeed;

        // Recharge based on braking strength
        mBattery->RegenCharge(speedDrop);
    }
    else
    {
        // Normal battery drain based on speed
        mBattery->ProgressiveDrain(mMotor->GetSpeed());
    }
}


void RegenerativeBraking::Report()
{
    std::cout << "Regenerative braking: "
              << (mActive ? "ACTIVE" : "inactive")
              << std::endl;
}
