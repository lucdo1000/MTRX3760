#include "RegenerativeBraking.h"

RegenerativeBraking::RegenerativeBraking(DriveMotor* motor, BatteryMonitor* battery)
    : mMotor(motor), mBattery(battery), mActive(false)
{
}

void RegenerativeBraking::Run()
{
    // Activate braking every second cycle
    mActive = !mActive;

    if(mActive)
    {
        // Slow the motor
        mMotor->ReduceSpeed(5);

        // Recharge battery slightly
        mBattery->Charge(2);
    }
}

void RegenerativeBraking::Report()
{
    std::cout << "Regenerative braking: "
              << (mActive ? "ACTIVE" : "inactive")
              << std::endl;
}
