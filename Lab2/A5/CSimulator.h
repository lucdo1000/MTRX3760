//-----------------------------------------------------------------------------
// CSimulator.h
//
// MTRX3760 Lab 2 - A5, Noise Bonus
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
//
// For the noise bonus the simulator places a fleet of each kind of robot
// instead of one, nudging every start pose by a small random amount, and it
// owns the single source of randomness those nudges and the wheels' slip are
// drawn from. Because that source is seeded once, here, the whole noisy run
// is still repeatable.
//-----------------------------------------------------------------------------

#ifndef CSIMULATOR_H
#define CSIMULATOR_H

#include "CNoise.h"
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
        // Loads the two maps and places a fleet of robots on each. Returns
        // false if either map could not be read, in which case there is
        // nothing to run.
        bool Build( const std::string& arWallsFile,
                    const std::string& arLineFile );

        //---Running---
        void Run();

    private:
        //---Steps of building---
        // The given start pose, moved and turned by a small random amount so
        // that no two robots of a fleet begin in quite the same place.
        CPose PerturbedStart( const CPose& arStartPose );

        //---Steps of the loop, one idea each---
        void UpdateRobots();
        void DrawFrame();
        bool AllRobotsFinished() const;
        void ReportSummary() const;
        // How many robots of one kind completed a lap, for the summary.
        int CountCompleted( const std::string& arKind ) const;

        //---Not copyable: it owns raw pointers and a window---
        CSimulator( const CSimulator& arOther );
        CSimulator& operator=( const CSimulator& arOther );

        //---Tuning---
        // One update is this much simulated time, regardless of real time.
        static const float FixedTimeStep;   // seconds of simulated time
        // A robot that has not finished by now is stuck; stop rather than hang.
        static const int MaximumUpdates;    // updates before giving up
        // The size of each fleet.
        static const int RobotsPerType;
        // How far a start pose may be nudged from the one in the map file.
        static const float StartPositionSpread;  // units, each of x and y
        static const float StartHeadingSpread;   // radians, either way

        //---Owned---
        CRender mRender;
        CWorld mWorld;
        CNoise mNoise;
        std::vector<CRobot*> mpRobots;

        //---Run state---
        int mUpdateCount;
        bool mIsRunning;
};

#endif
