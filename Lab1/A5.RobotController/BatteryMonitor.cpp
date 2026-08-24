// BatteryMonitor.cpp
//
// Implementation file for the robot's battery.

#include "BatteryMonitor.h"
#include <iostream>

//---BatteryMonitor Implementation------------------------------------
BatteryMonitor::BatteryMonitor()
    : mLevel(100), mLastDrain(0), mLastCharge(0)
{
}

// Battery level only ever changes through Drain()/Charge(), called by
// RegenerativeBraking once it knows what kind of cycle this is. There
// is nothing for the battery to do on its own here.
void BatteryMonitor::Run()
{
}

void BatteryMonitor::Report()
{
    std::cout << "Battery: ";

    // mLastCharge and mLastDrain can't both be nonzero, so exactly one
    // of these branches fires
    if(mLastCharge > 0)
        std::cout << "+" << mLastCharge << "% regen charge";
    else if(mLastDrain > 0)
        std::cout << "-" << mLastDrain << "% drive drain";
    else
        std::cout << "no change";

    std::cout << " -> " << mLevel << "%" << std::endl;
}

void BatteryMonitor::Drain(int motorSpeed)
{
    int before = mLevel;

    int drain = 5;             // base drain, just for being switched on
    drain += motorSpeed / 5;   // every 5 speed adds 1 more drain

    mLevel -= drain;
    if(mLevel < 0) mLevel = 0;

    // the real drop, not just drain, in case the floor above clipped it
    mLastDrain = before - mLevel;
    mLastCharge = 0;
}

void BatteryMonitor::Charge(int speedDrop)
{
    int before = mLevel;

    int charge = 2;               // base regen, just for braking at all
    charge += speedDrop / 10;     // every 10 speed dropped adds 1 more charge

    mLevel += charge;
    if(mLevel > 100) mLevel = 100;

    mLastCharge = mLevel - before;   // same clipping logic as Drain() above
    mLastDrain = 0;
}
