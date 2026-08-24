// ISubsystem.h
//
// Interface that every robot subsystem implements.

#ifndef ISUBSYSTEM_H
#define ISUBSYSTEM_H

//---------------------------------------------------------------
// The common contract every subsystem obeys, so Controller can hold a
// list of subsystems of different concrete types (DriveMotor,
// BatteryMonitor, RegenerativeBraking, ...) and drive them all the same
// way without knowing which is which. That uniform treatment of
// different concrete types through one interface is polymorphism.
class ISubsystem
{
public:
    virtual ~ISubsystem() {}   // virtual so deleting through an ISubsystem* is safe

    virtual void Run() = 0;        // advance this subsystem by one cycle
    virtual void Report() = 0;     // print this subsystem's current state
};

#endif
