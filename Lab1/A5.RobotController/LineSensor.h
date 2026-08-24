#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "ISubsystem.h"
#include <iostream>

class LineSensor : public ISubsystem
{
public:
    LineSensor();

    void Run() override;
    void Report() override;

private:
    int mBrightness;
};

#endif
