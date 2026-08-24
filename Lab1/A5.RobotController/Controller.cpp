#include "Controller.h"
#include <iostream>

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

    // Two-phase update: every subsystem updates its state first,
    // then every subsystem reports. This guarantees Report() always
    // reflects this cycle's state, regardless of add order or
    // cross-subsystem dependencies (e.g. braking changing motor speed).
    for(ISubsystem* s : mSubsystems)
        s->Run();

    for(ISubsystem* s : mSubsystems)
        s->Report();
}