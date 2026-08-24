#include "Controller.h"
#include "DriveMotor.h"
#include "BatteryMonitor.h"
#include "RegenerativeBraking.h"

int main()
{
    const int kNumCycles = 12;   // long enough to see brakes engage and release more than once

    Controller robot;

    DriveMotor motor;
    BatteryMonitor battery;
    RegenerativeBraking brakes(&motor, &battery);

    // Run order matters: brakes reads the motor's speed for this cycle and
    // may adjust it, so the motor must run first. Battery only reacts to
    // calls made by brakes, so it can run last.
    robot.AddSubsystem(&motor);
    robot.AddSubsystem(&brakes);
    robot.AddSubsystem(&battery);

    for(int i = 0; i < kNumCycles; ++i)
    {
        robot.RunCycle();
    }

    return 0;
}
