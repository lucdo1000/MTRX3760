//-----------------------------------------------------------------------------
// main.cpp
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// MTRX3760 Lab 2, A1: a robot that drives around a room following the wall on
// its right hand side.
//
// BUILDING (raylib installed with apt)
//
//     g++ -Wall -Wextra *.cpp -lraylib -o RobotSimulator
//
// BUILDING (raylib built from source into your home directory)
//
//     g++ -Wall -Wextra *.cpp -I$HOME/raylib/include -L$HOME/raylib/lib -lraylib -o RobotSimulator
//
// RUNNING
//
//     ./RobotSimulator
//
// CSimulator owns everything, so there is nothing to assemble here.
//-----------------------------------------------------------------------------

#include "CSimulator.h"

#include <iostream>

namespace
{
    const char* const WallsMapFile = "SimpleWalls.map";
}

//-----------------------------------------------------------------------------
int main()
{
    int Result = 1;

    CSimulator Simulator;

    if( Simulator.Build( WallsMapFile ) )
    {
        Simulator.Run();
        Result = 0;
    }
    else
    {
        std::cout << "Could not start: check the map file is beside the "
                  << "program." << std::endl;
    }

    return Result;
}
