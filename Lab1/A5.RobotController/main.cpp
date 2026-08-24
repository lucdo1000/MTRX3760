#include "Controller.h"
#include "DriveMotor.h"
#include "LineSensor.h"
#include "BatteryMonitor.h"

int main()
{
    Controller robot;

    DriveMotor motor;
    LineSensor sensor;
    BatteryMonitor battery;

    robot.AddSubsystem(&motor);
    robot.AddSubsystem(&sensor);
    robot.AddSubsystem(&battery);

    for(int i = 0; i < 3; ++i)
    {
        robot.RunCycle();
    }

    return 0;
}
