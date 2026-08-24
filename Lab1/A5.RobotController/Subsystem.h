#ifndef ISUBSYSTEM_H
#define ISUBSYSTEM_H

class ISubsystem
{
public:
    virtual ~ISubsystem() {}

    virtual void Run() = 0;        // update internal state
    virtual void Report() = 0;     // print current state
};

#endif
