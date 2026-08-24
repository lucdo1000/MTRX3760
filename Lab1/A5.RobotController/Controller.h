#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ISubsystem.h"
#include <vector>

class Controller
{
public:
    void AddSubsystem(ISubsystem* s);
    void RunCycle();

private:
    std::vector<ISubsystem*> mSubsystems;
};

#endif
