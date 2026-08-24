// main.cpp
//
// Builds one robot out of three subsystems and runs it for a fixed
// number of cycles. See ISubsystem.h, DriveMotor.h, BatteryMonitor.h,
// RegenerativeBraking.h and Controller.h for how the pieces fit together.

#include "Controller.h"
#include "DriveMotor.h"
#include "BatteryMonitor.h"
#include "RegenerativeBraking.h"

int main()
{
    const int kNumCycles = 12;   // long enough to see brakes engage and release more than once

    Controller robot;

    // Owned here, not by Controller or RegenerativeBraking, both just
    // hold pointers to them. Must outlive robot.
    DriveMotor motor;
    BatteryMonitor battery;
    RegenerativeBraking brakes(&motor, &battery);

    // Registration order only decides print order within a cycle (motor,
    // then braking status, then battery), it doesn't affect behaviour.
    // DriveMotor and BatteryMonitor's own Run() do nothing, all the real
    // state changes happen inside RegenerativeBraking::Run(), through
    // the direct pointers above rather than Controller's subsystem list.
    robot.AddSubsystem(&motor);
    robot.AddSubsystem(&brakes);
    robot.AddSubsystem(&battery);

    for(int i = 0; i < kNumCycles; ++i)
    {
        robot.RunCycle();
    }

    return 0;
}
