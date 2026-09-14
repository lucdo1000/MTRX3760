
// main.cpp
//
// MTRX3760 Lab 2 - A5, Noise Bonus
// Written by SID 540700701 and SID 530838753
// Practical section: Practical Session 2
//
//
// MTRX3760 Lab 2, A5: twenty wall followers and twenty line followers sharing
// one room, each starting from a slightly different place and each with wheels
// that slip a little, so no two take the same path.
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

#include "CSimulator.h"

#include <iostream>

namespace
{
    const char* const WallsMapFile = "SimpleWalls.map";
    const char* const LineMapFile = "SimpleLine.map";
}

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
