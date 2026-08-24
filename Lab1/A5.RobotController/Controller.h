// Controller.h
//
// Header file for the robot controller.

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ISubsystem.h"
#include <vector>

//---Controller Interface----------------------------------------
// Runs a robot made of any number of subsystems, without knowing what
// any of them actually are, it only ever sees them through ISubsystem.
// A new subsystem, a line sensor, a heater, whatever, just needs a
// class that implements ISubsystem and a call to AddSubsystem().
// Controller itself never has to change.
class Controller
{
public:
    Controller();

    // registers a subsystem to run every cycle. Controller does not own
    // it, whoever constructs the subsystem (see main.cpp) has to keep
    // it alive for as long as the controller runs.
    void AddSubsystem(ISubsystem* s);

    // advances every registered subsystem by one cycle and reports their state
    void RunCycle();

private:
    std::vector<ISubsystem*> mSubsystems;
    int mCycleCount;   // cycles run so far, for the report header
};

#endif
