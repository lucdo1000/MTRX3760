//-----------------------------------------------------------------------------
// CSimulator.h
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// The object that owns the whole simulation.
//
// It holds the window, the world and every robot in it, and it runs the loop
// that advances them. Because it owns all of that, main() only has to create
// one of these and run it - there is nothing else to build by hand.
//
// Each pass of the loop advances the simulation by a fixed slice of simulated
// time, not by however long the last frame happened to take. That keeps a run
// repeatable: the same program produces the same trajectories whatever the
// machine is doing, which is what makes a result worth reporting.
//-----------------------------------------------------------------------------

#ifndef CSIMULATOR_H
#define CSIMULATOR_H

#include "CRender.h"
#include "CRobot.h"
#include "CWorld.h"

#include <string>
#include <vector>

//-----------------------------------------------------------------------------
class CSimulator
{
    public:
        //---Ctor/Dtor---
        CSimulator();
        ~CSimulator();

        //---Setting up---
        // Loads the room and places the robot in it. Returns false if the map
        // could not be read, in which case there is nothing to run.
        bool Build( const std::string& arWallsFile );

        //---Running---
        void Run();

    private:
        //---Steps of the loop, one idea each---
        void UpdateRobots();
        void DrawFrame();
        bool AllRobotsFinished() const;
        void ReportSummary() const;

        //---Not copyable: it owns raw pointers and a window---
        CSimulator( const CSimulator& arOther );
        CSimulator& operator=( const CSimulator& arOther );

        //---Tuning---
        // One update is this much simulated time, regardless of real time.
        static const float FixedTimeStep;   // seconds of simulated time
        // A robot that has not finished by now is stuck; stop rather than hang.
        static const int MaximumUpdates;    // updates before giving up

        //---Owned---
        CRender mRender;
        CWorld mWorld;
        std::vector<CRobot*> mpRobots;

        //---Run state---
        int mUpdateCount;
        bool mIsRunning;
};

#endif
