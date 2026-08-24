// ISubsystem.h
//
// Interface every robot subsystem implements.

#ifndef ISUBSYSTEM_H
#define ISUBSYSTEM_H

//---ISubsystem Interface----------------------------------------
// The common contract every subsystem obeys. Controller only ever holds
// ISubsystem pointers, so it can run a DriveMotor, a BatteryMonitor and
// a RegenerativeBraking the same way, without knowing which is which.
class ISubsystem
{
public:
    // virtual, so deleting through an ISubsystem* is safe
    virtual ~ISubsystem() {}

    // advance this subsystem by one cycle
    virtual void Run() = 0;

    // print this subsystem's current state
    virtual void Report() = 0;
};

#endif
