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
