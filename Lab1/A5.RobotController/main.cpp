#include "Controller.h"
#include "DriveMotor.h"
#include "LineSensor.h"
#include "BatteryMonitor.h"

int main()
{
    Controller robot;

    DriveMotor motor;
    BatteryMonitor battery;
    RegenerativeBreaking brakes(&motor, &battery)
    
    robot.AddSubsystem(&motor);
    robot.AddSubsystem(&battery);
    robot.AddSubsystem(&brakes);
    
    for(int i = 0; i < 3; ++i)
    {
        robot.RunCycle();
    }

    return 0;
}
