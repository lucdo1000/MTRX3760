#include "BatteryMonitor.h"

BatteryMonitor::BatteryMonitor()
    : mLevel(100), mLastDrain(0), mLastCharge(0)
{
}

void BatteryMonitor::Run()
{
    // Battery level only changes via Drain() / Charge(), called by
    // RegenerativeBraking once it knows whether this cycle is a drive
    // cycle or a braking cycle. Nothing to do here on our own.
}

void BatteryMonitor::Report()
{
    std::cout << "Battery: ";
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
    int drain = 5;
    drain += motorSpeed / 5;   // every +5 speed adds +1 drain

    mLevel -= drain;
    if(mLevel < 0) mLevel = 0;

    mLastDrain = before - mLevel;
    mLastCharge = 0;   // draining and charging can't both happen this cycle
}

void BatteryMonitor::Charge(int speedDrop)
{
    int before = mLevel;
    int charge = 2;
    charge += speedDrop / 10;   // every -10 speed adds +1 charge

    mLevel += charge;
    if(mLevel > 100) mLevel = 100;

    mLastCharge = mLevel - before;
    mLastDrain = 0;
}