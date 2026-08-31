//-----------------------------------------------------------------------------
// main.cpp
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// MTRX3760 Lab 2, A2: a wall following robot and a line following robot sharing
// one room.
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
    const char* const LineMapFile = "SimpleLine.map";
}

//-----------------------------------------------------------------------------
int main()
{
    int Result = 1;

    CSimulator Simulator;

    if( Simulator.Build( WallsMapFile, LineMapFile ) )
    {
        Simulator.Run();
        Result = 0;
    }
    else
    {
        std::cout << "Could not start: check the map files are beside the "
                  << "program." << std::endl;
    }

    return Result;
}
