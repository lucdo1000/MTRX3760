// CSimulator.cpp
//
// This version runs two different robot types in the same simulation. The world
// supplies both the wall loop and the painted line loop, and the simulator just
// keeps both robots moving at the same fixed time step.

#include "CSimulator.h"
#include "CWallFollower.h"
#include "CLineFollower.h"

#include <iostream>

// One sixtieth of a second of simulated time per update.
const float CSimulator::FixedTimeStep = 1.0f / 60.0f;
const int CSimulator::MaximumUpdates = 10000;

CSimulator::CSimulator()
    :
        mRender(),
        mWorld(),
        mpRobots(),
        mUpdateCount( 0 ),
        mIsRunning( true )
{
}

// The simulator created the robots, so the simulator destroys them.
CSimulator::~CSimulator()
{
    for( std::size_t i = 0; i < mpRobots.size(); ++i )
    {
        delete mpRobots[i];
    }
}

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
        // The wall robot and the line robot each start from their own named pose in
        // the same world, which is the main difference from A1.
        mpRobots.push_back( new CWallFollower( mWorld.GetWallStartPose() ) );
        mpRobots.push_back( new CLineFollower( mWorld.GetLineStartPose() ) );
    }

    return Result;
}

// The window stays open after the run finishes so the completed trails can be
// looked at, which is why updating and drawing are separated: drawing carries
// on after updating has stopped.
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

void CSimulator::UpdateRobots()
{
    for( std::size_t i = 0; i < mpRobots.size(); ++i )
    {
        mpRobots[i]->Update( mWorld, FixedTimeStep );
    }
}

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

bool CSimulator::AllRobotsFinished() const
{
    bool Result = true;

    for( std::size_t i = 0; ( i < mpRobots.size() ) && Result; ++i )
    {
        Result = mpRobots[i]->HasCompletedLap();
    }

    return Result;
}

void CSimulator::ReportSummary() const
{
    int TotalCollisions = 0;

    std::cout << std::endl;
    std::cout << "--- Run complete ---" << std::endl;
    std::cout << "Updates completed: " << mUpdateCount << std::endl;

    for( std::size_t i = 0; i < mpRobots.size(); ++i )
    {
        const CRobot& rRobot = *mpRobots[i];
        TotalCollisions += rRobot.GetCollisionCount();

        std::cout << "  " << rRobot.GetName() << ": "
                  << ( rRobot.HasCompletedLap() ? "completed its lap"
                                                : "did NOT complete its lap" )
                  << ", " << rRobot.GetCollisionCount() << " collisions"
                  << std::endl;
    }

    std::cout << "Total collisions: " << TotalCollisions << std::endl;
}
