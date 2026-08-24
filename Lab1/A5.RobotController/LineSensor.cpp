#include "LineSensor.h"

LineSensor::LineSensor()
    : mBrightness(0)
{
}

void LineSensor::Run()
{
    mBrightness = (mBrightness + 3) % 100;   // brightness cycles
}

void LineSensor::Report()
{
    std::cout << "LineSensor brightness: " << mBrightness << std::endl;
}
