#include "Controller.h"
#include <iostream>

void Controller::AddSubsystem(ISubsystem* s)
{
    mSubsystems.push_back(s);
}

void Controller::RunCycle()
{
    std::cout << "--- Cycle ---" << std::endl;

    for(ISubsystem* s : mSubsystems)
    {
        s->Run();
        s->Report();
    }
}
