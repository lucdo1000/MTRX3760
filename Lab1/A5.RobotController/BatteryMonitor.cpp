#include "BatteryMonitor.h"

BatteryMonitor::BatteryMonitor()
    : mLevel(100)
{
}

void BatteryMonitor::Run()
{
    mLevel -= 5;          // battery drains each cycle
    if(mLevel < 0)
        mLevel = 0;
}

void BatteryMonitor::Report()
{
    std::cout << "Battery level: " << mLevel << "%" << std::endl;
}

void BatteryMonitor::Charge(int amount)
{
    mLevel += amount;
    if(mLevel > 100) mLevel = 100;
}

void BatteryMonitor::ProgressiveDrain(int motorSpeed)
{
    // Base drain
    int drain = 5;

    // Extra drain based on speed
    drain += motorSpeed / 5;   // every +20 speed adds +1 drain

    mLevel -= drain;
    if(mLevel < 0) mLevel = 0;
}

void BatteryMonitor::RegenCharge(int speedDrop)
{
    // Base regen
    int charge = 2;

    // More regen for sharper braking
    charge += speedDrop / 10;   // every -10 speed adds +1 charge

    mLevel += charge;
    if(mLevel > 100) mLevel = 100;
}
