//-----------------------------------------------------------------------------
// CWheel.h
//
// MTRX3760 Lab 2 - A5, Noise Bonus
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// One of a robot's two independently driven wheels.
//
// A wheel knows how fast it has been told to turn and how far it sits to the
// side of the robot's centre. Keeping the offset here rather than in CRobot is
// what lets the differential drive read as "ask each wheel where it is and how
// fast it is going" instead of arithmetic on a bare pair of numbers.
//
// For the noise bonus the wheel also answers "how far did you actually turn
// this step?" - and the answer is not quite what was commanded, for two
// reasons a real wheel has. No two wheels are made quite the same size, so
// each carries a fixed error of its own, drawn once when it is built. And a
// wheel slips a little on every step, so each step carries a fresh error on
// top. The fixed part is what makes one robot pull gently left and another
// right, giving each its own path; the fresh part is what makes the paths
// wobble. Putting both here rather than in the robot is the point of having
// a wheel class at all: the robot asks for distances and gets honest ones,
// and it never sees the noise.
//-----------------------------------------------------------------------------

#ifndef CWHEEL_H
#define CWHEEL_H

class CNoise;

//-----------------------------------------------------------------------------
class CWheel
{
    public:
        //---Ctor---
        // aLateralOffset is measured to the robot's right, so the left wheel
        // takes a negative offset and the right wheel a positive one. The
        // wheel draws its own fixed size error from arNoise as it is built.
        CWheel( float aLateralOffset, CNoise& arNoise );

        //---Speed---
        void SetSpeed( float aSpeed );      // units of distance per second
        float GetSpeed() const;

        //---Travel---
        // The distance this wheel actually covered in one step of aDeltaTime:
        // the commanded distance, scaled by this wheel's fixed error and by a
        // fresh random slip.
        float Travel( float aDeltaTime, CNoise& arNoise ) const;

        //---Placement---
        float GetLateralOffset() const;

    private:
        //---Tuning---
        // Both errors are fractions of the commanded travel, so a wheel that
        // is not turning does not creep.
        static const float SizeErrorSpread;  // fixed per wheel; 0.08 = within 8%
        static const float SlipSpread;       // fresh every step

        //---State---
        float mSpeed;                  // units of distance per second
        const float mLateralOffset;    // units, positive to the robot's right
        const float mSizeError;        // fraction; this wheel's own, for life
};

#endif
