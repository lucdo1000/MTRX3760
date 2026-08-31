//-----------------------------------------------------------------------------
// CRobot.h
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// Everything the two robots share, which is nearly all of it.
//
// The handout describes one robot twice: a disc of a fixed radius, driven by
// two independently controlled wheels, advanced by a fixed slice of simulated
// time each update, drawn as a circle with a heading indicator, leaving a trail
// behind it. The only difference between the wall follower and the line
// follower is what they sense and how they decide to steer.
//
// So the common half lives here and the differing half is left abstract.
// A derived class must answer two questions: how does it sense and steer
// (SenseAndSteer), and how does it draw whatever sensors it happens to carry
// (DrawSensors). It never touches the kinematics, the trail, collision counting
// or lap detection, because none of those differ between the two robots.
//
// This is the class to look at first when reading the design: it is where the
// decision about what is shared and what varies has been made.
//-----------------------------------------------------------------------------

#ifndef CROBOT_H
#define CROBOT_H

#include "CLoopReader.h"   // for CPose
#include "CRender.h"
#include "CTrail.h"
#include "CWheel.h"

#include <string>

class CWorld;

//-----------------------------------------------------------------------------
class CRobot
{
    public:
        //---Ctor/Dtor---
        CRobot( const std::string& arName, const CPose& arStartPose,
                Color aBodyColour, Color aTrailColour );
        virtual ~CRobot();

        //---Simulation---
        // Advances this robot by one fixed slice of simulated time.
        void Update( const CWorld& arWorld, float aDeltaTime );

        //---Drawing---
        void Draw( CRender& arRender ) const;

        //---Reporting---
        const std::string& GetName() const;
        const CPose& GetPose() const;
        int GetCollisionCount() const;
        bool HasCompletedLap() const;

        //---Shared dimensions---
        static float GetBodyRadius();

    protected:
        //---What each kind of robot must supply---
        // Read the sensors this robot carries and set the two wheel speeds.
        virtual void SenseAndSteer( const CWorld& arWorld ) = 0;
        // Draw whatever sensors this robot carries.
        virtual void DrawSensors( CRender& arRender ) const = 0;

        //---Available to derived classes when steering---
        void Drive( float aLeftSpeed, float aRightSpeed );

    private:
        //---Steps of one update, kept separate so each reads as one idea---
        void AdvancePose( float aDeltaTime );
        void CheckForCollision( const CWorld& arWorld );
        void CheckForLapCompletion();

        //---Shared dimensions and tuning---
        static const float BodyRadius;       // units; fixed at 15 by the handout
        static const float WheelOffset;      // units, each wheel out from centre
        static const float HeadingLineScale; // multiple of the body radius
        static const float TrailThickness;   // units, drawn width of the trail
        // The robot must get at least this far from where it started before
        // coming home can count as a completed lap, so that jitter at the start
        // cannot be mistaken for a lap.
        static const float LapDepartureDistance;  // units from the start pose
        static const float LapReturnDistance;     // units; back inside = a lap

        //---Identity---
        const std::string mName;

        //---State---
        CPose mPose;
        CWheel mLeftWheel;
        CWheel mRightWheel;
        CTrail mTrail;
        const Color mBodyColour;

        //---Where it began, for lap detection---
        const Vec2D mStartPosition;
        bool mHasLeftStart;
        bool mLapComplete;

        //---Collisions. mWasColliding makes one contact count once---
        int mCollisionCount;
        bool mWasColliding;
};

#endif
