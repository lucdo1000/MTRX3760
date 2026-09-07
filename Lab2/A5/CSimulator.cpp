//-----------------------------------------------------------------------------
// CSimulator.cpp
//
// MTRX3760 Lab 2 - A5, Noise Bonus
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CSimulator.h"
#include "CGeometry.h"
#include "CWallFollower.h"
#include "CLineFollower.h"

#include <iostream>

namespace
{
    const float Degrees30 = 0.523599f;
}

//---One sixtieth of a second of simulated time per update---
const float CSimulator::FixedTimeStep = 1.0f / 60.0f;
// A clean lap takes about 1600 updates; a noisy one a little more. Anything
// still going at twice that is lost, and there are forty robots to wait for.
const int CSimulator::MaximumUpdates = 3200;
const int CSimulator::RobotsPerType = 20;
// The wall follower's start is 40 units from the nearest wall, so 20 is as
// far as it can be nudged and still be placed clear of it.
const float CSimulator::StartPositionSpread = 20.0f;
const float CSimulator::StartHeadingSpread = Degrees30;

//-----------------------------------------------------------------------------
CSimulator::CSimulator()
    :
        mRender(),
        mWorld(),
        mNoise(),
        mpRobots(),
        mUpdateCount( 0 ),
        mIsRunning( true )
{
}

//-----------------------------------------------------------------------------
// The simulator created the robots, so the simulator destroys them.
//-----------------------------------------------------------------------------
CSimulator::~CSimulator()
{
    for( std::size_t i = 0; i < mpRobots.size(); ++i )
    {
        delete mpRobots[i];
    }
}

//-----------------------------------------------------------------------------
bool CSimulator::Build( const std::string& arWallsFile,
                        const std::string& arLineFile )
{
    const bool WallsLoaded = mWorld.LoadWalls( arWallsFile );
    const bool LineLoaded = mWorld.LoadLine( arLineFile );

    if( !WallsLoaded )
    {
        std::cout << "Could not read the walls map: " << arWallsFile << std::endl;
    }

    if( !LineLoaded )
    {
        std::cout << "Could not read the line map: " << arLineFile << std::endl;
    }

    const bool Result = WallsLoaded && LineLoaded;

    if( Result )
    {
        //---Each fleet starts near the pose named in its own map file---
        for( int i = 0; i < RobotsPerType; ++i )
        {
            mpRobots.push_back( new CWallFollower(
                i, PerturbedStart( mWorld.GetWallStartPose() ), mNoise ) );
        }

        for( int i = 0; i < RobotsPerType; ++i )
        {
            mpRobots.push_back( new CLineFollower(
                i, PerturbedStart( mWorld.GetLineStartPose() ), mNoise ) );
        }
    }

    return Result;
}

//-----------------------------------------------------------------------------
// Position and heading are nudged independently, so a robot can begin a
// little off the mark, a little off its heading, or both. Nudging the start
// rather than the robot means lap detection, which measures from wherever a
// robot began, needs no special case.
//-----------------------------------------------------------------------------
CPose CSimulator::PerturbedStart( const CPose& arStartPose )
{
    CPose Result = arStartPose;

    Result.mPosition.x += mNoise.Uniform( StartPositionSpread );
    Result.mPosition.y += mNoise.Uniform( StartPositionSpread );
    Result.mHeading = CGeometry::NormaliseAngle(
        Result.mHeading + mNoise.Uniform( StartHeadingSpread ) );

    return Result;
}

//-----------------------------------------------------------------------------
// The window stays open after the run finishes so the completed trails can be
// looked at, which is why updating and drawing are separated: drawing carries
// on after updating has stopped.
//-----------------------------------------------------------------------------
void CSimulator::Run()
{
    while( !mRender.WindowShouldClose() )
    {
        if( mIsRunning )
        {
            UpdateRobots();
            ++mUpdateCount;

            if( AllRobotsFinished() || ( mUpdateCount >= MaximumUpdates ) )
            {
                mIsRunning = false;
                ReportSummary();
            }
        }

        DrawFrame();
    }

    mRender.CloseWindow();
}

//-----------------------------------------------------------------------------
void CSimulator::UpdateRobots()
{
    for( std::size_t i = 0; i < mpRobots.size(); ++i )
    {
        mpRobots[i]->Update( mWorld, mNoise, FixedTimeStep );
    }
}

//-----------------------------------------------------------------------------
void CSimulator::DrawFrame()
{
    mRender.BeginDrawing();

    mWorld.Draw( mRender );

    for( std::size_t i = 0; i < mpRobots.size(); ++i )
    {
        mpRobots[i]->Draw( mRender );
    }

    mRender.EndDrawing();
}

//-----------------------------------------------------------------------------
bool CSimulator::AllRobotsFinished() const
{
    bool Result = true;

    for( std::size_t i = 0; ( i < mpRobots.size() ) && Result; ++i )
    {
        Result = mpRobots[i]->HasCompletedLap();
    }

    return Result;
}

//-----------------------------------------------------------------------------
// With forty robots the useful number is how many of each fleet made it, so
// that is what leads; the per-robot lines follow for anyone who wants them.
//-----------------------------------------------------------------------------
void CSimulator::ReportSummary() const
{
    int TotalCollisions = 0;

    std::cout << std::endl;
    std::cout << "--- Run complete ---" << std::endl;
    std::cout << "Updates completed: " << mUpdateCount << std::endl;
    std::cout << "  " << CWallFollower::Kind << ": "
              << CountCompleted( CWallFollower::Kind ) << " of "
              << RobotsPerType << " completed a lap" << std::endl;
    std::cout << "  " << CLineFollower::Kind << ": "
              << CountCompleted( CLineFollower::Kind ) << " of "
              << RobotsPerType << " completed a lap" << std::endl;

    for( std::size_t i = 0; i < mpRobots.size(); ++i )
    {
        const CRobot& rRobot = *mpRobots[i];
        TotalCollisions += rRobot.GetCollisionCount();

        std::cout << "    " << rRobot.GetName() << ": "
                  << ( rRobot.HasCompletedLap() ? "completed its lap"
                                                : "did NOT complete its lap" )
                  << ", " << rRobot.GetCollisionCount() << " collisions"
                  << std::endl;
    }

    std::cout << "Total collisions: " << TotalCollisions
              << " (not counted for the noise bonus)" << std::endl;
}

//-----------------------------------------------------------------------------
int CSimulator::CountCompleted( const std::string& arKind ) const
{
    int Result = 0;

    for( std::size_t i = 0; i < mpRobots.size(); ++i )
    {
        if( ( mpRobots[i]->GetKind() == arKind )
            && mpRobots[i]->HasCompletedLap() )
        {
            ++Result;
        }
    }

    return Result;
}
