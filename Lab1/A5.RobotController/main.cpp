#include "Controller.h"
#include "DriveMotor.h"
#include "BatteryMonitor.h"
#include "RegenerativeBraking.h"

int main()
{
    Controller robot;

    DriveMotor motor;
    BatteryMonitor battery;
    RegenerativeBraking brakes(&motor, &battery);
    
    robot.AddSubsystem(&motor);
    robot.AddSubsystem(&brakes);
    robot.AddSubsystem(&battery);
    
    for(int i = 0; i < 5; ++i)
    {
        robot.RunCycle();
    }

    return 0;
}
