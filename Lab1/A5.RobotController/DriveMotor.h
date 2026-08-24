#ifndef DRIVEMOTOR_H
#define DRIVEMOTOR_H

#include "ISubsystem.h"
#include <iostream>

class DriveMotor : public ISubsystem
{
public:
    DriveMotor();

    void Run() override;
    void Report() override;

    void ReduceSpeed(int amount);

private:
    int mSpeed;
};

#endif
