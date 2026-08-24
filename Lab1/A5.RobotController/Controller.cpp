// Controller.cpp
//
// Implementation file for the robot controller.

#include "Controller.h"
#include <iostream>

//---------------------------------------------------------------
Controller::Controller()
    : mCycleCount(0)
{
}

//---------------------------------------------------------------
void Controller::AddSubsystem(ISubsystem* s)
{
    mSubsystems.push_back(s);
}

//---------------------------------------------------------------
void Controller::RunCycle()
{
    ++mCycleCount;
    std::cout << "--- Cycle " << mCycleCount << " ---" << std::endl;

    // Two-phase update: every subsystem updates its state first,
    // then every subsystem reports. This guarantees Report() always
    // reflects this cycle's state, regardless of add order or
    // cross-subsystem dependencies (e.g. braking changing motor speed).
    //
    // s is an ISubsystem* here, not a DriveMotor*/BatteryMonitor*/
    // RegenerativeBraking* — Controller calls Run()/Report() through the
    // interface and the right override runs for whatever concrete
    // subsystem s actually points to. That's polymorphism: this loop
    // doesn't change no matter how many kinds of subsystem get added.
    for(ISubsystem* s : mSubsystems)
        s->Run();

    for(ISubsystem* s : mSubsystems)
        s->Report();
}