// Controller.cpp
//
// Implementation file for the robot controller.

#include "Controller.h"
#include <iostream>

// Constructor -- sets cycle count to 0
Controller::Controller()
    : mCycleCount(0)
{
}

void Controller::AddSubsystem(ISubsystem* s)
{
    // Adds a new object s to the vector (list)
    mSubsystems.push_back(s);
}

void Controller::RunCycle()
{
    ++mCycleCount;
    std::cout << "--- Cycle " << mCycleCount << " ---" << std::endl;

    // Two passes: every subsystem updates first, then every subsystem reports so that Report() always reflects this cycle's state
    // The common interfaces for all subsystems
    for(ISubsystem* s : mSubsystems)
        s->Run();

    for(ISubsystem* s : mSubsystems)
        s->Report();
}
