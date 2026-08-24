// Controller.cpp
//
// Implementation file for the robot controller.

#include "Controller.h"
#include <iostream>

//---Controller Implementation--------------------------------------
Controller::Controller()
    : mCycleCount(0)
{
}

void Controller::AddSubsystem(ISubsystem* s)
{
    mSubsystems.push_back(s);
}

void Controller::RunCycle()
{
    ++mCycleCount;
    std::cout << "--- Cycle " << mCycleCount << " ---" << std::endl;

    // two passes: every subsystem updates first, then every subsystem
    // reports. That way Report() always reflects this cycle's state, no
    // matter what order subsystems were added in or how they depend on
    // each other (braking changes the motor's speed, for example).
    //
    // s is an ISubsystem* here, not a DriveMotor* or a
    // RegenerativeBraking*. Run()/Report() dispatch to whichever
    // concrete subsystem s actually points to. That's polymorphism,
    // this loop doesn't change no matter how many kinds get added.
    for(ISubsystem* s : mSubsystems)
        s->Run();

    for(ISubsystem* s : mSubsystems)
        s->Report();
}
