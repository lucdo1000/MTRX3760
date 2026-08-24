#include "Controller.h"
#include "DriveMotor.h"
#include "LineSensor.h"

int main()
{
    Controller robot;

    DriveMotor motor;
    LineSensor sensor;

    robot.AddSubsystem(&motor);
    robot.AddSubsystem(&sensor);

    for(int i = 0; i < 3; ++i)
    {
        robot.RunCycle();
    }

    return 0;
}
