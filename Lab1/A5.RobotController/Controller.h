// Controller.h
//
// Header file for the robot controller.

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ISubsystem.h"
#include <vector>

//---------------------------------------------------------------
// Runs a robot made of any number of subsystems, without knowing what
// any of them actually are — it only ever sees them through the
// ISubsystem interface. New subsystems (a line sensor, a heater, ...)
// can be added just by writing a class that implements ISubsystem and
// calling AddSubsystem(); Controller itself never needs to change.
class Controller
{
public:
    Controller();

    // Registers a subsystem to be run every cycle. Controller does not
    // own it — whoever constructs the subsystem (see main.cpp) is
    // responsible for keeping it alive for as long as the controller runs.
    void AddSubsystem(ISubsystem* s);

    // Advances every registered subsystem by one cycle and prints their
    // state.
    void RunCycle();

private:
    std::vector<ISubsystem*> mSubsystems;
    int mCycleCount;   // how many cycles have run so far, for the report header
};

#endif