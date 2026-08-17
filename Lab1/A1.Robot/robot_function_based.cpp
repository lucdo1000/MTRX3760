// A line-following robot (function-based version)
//
// This program models a robot that follows a line. Each cycle the robot reads
// its line sensor, works out how hard to steer, and sets its two drive motors.
// Each part of the robot is a struct, and free functions operate on those
// structs by taking them as arguments.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <stdio.h>

//--Consts---------------------------------------------------------------------
const int NumCycles = 4;              // how many cycles the robot runs for
const double BaseSpeed = 0.5;         // forward speed before steering is added

//---SLineSensor---------------------------------------------------------------
// SLineSensor reports how far the robot is off the line. It remembers which
// cycle it is up to so that successive reads walk along the track.
struct SLineSensor
{
  int cycle;              // how many readings have been taken so far
};

//---SController---------------------------------------------------------------
// SController turns an off-line reading into a steering amount. It remembers
// the previous reading so it can respond to how fast the error is changing.
struct SController
{
  double lastError;       // the reading from the previous cycle
};

//---SMotor--------------------------------------------------------------------
// SMotor holds one drive motor's label and its current speed.
struct SMotor
{
  const char* pName;      // the motor's label, e.g. "Left"
  double speed;           // current speed, -1.0 to 1.0
};

// ----SBattery------------------------------------------------------------------
// SBattery holds the battery's charge level.
struct SBattery
{
  double charge;         // 0-100%
};

//---Function declarations-----------------------------------------------------
void InitLineSensor( SLineSensor* apSensor );
void InitController( SController* apController );
void InitMotor( SMotor* apMotor, const char* aName );
void InitBattery( SBattery* apBattery );

int ReadLineSensor( SLineSensor* apSensor );
double ComputeSteering( SController* apController, int aError );
void SetMotorSpeed( SMotor* apMotor, double aSpeed );

void UpdateRobot( SLineSensor* apSensor, SController* apController,
                  SMotor* apLeftMotor, SMotor* apRightMotor, SBattery* apBattery );
void ReportRobot( SMotor* apLeftMotor, SMotor* apRightMotor );

//---main----------------------------------------------------------------------
// Sets up each part of the robot, then runs it for a number of cycles,
// reporting the motors after each one.
int main()
{
  SLineSensor sensor;
  SController controller;
  SMotor leftMotor;
  SMotor rightMotor;
  SBattery battery;

  InitLineSensor( &sensor );
  InitController( &controller );
  InitMotor( &leftMotor, "Left" );
  InitMotor( &rightMotor, "Right" );
  InitBattery( &battery );

  for( int i = 0; i < NumCycles; ++i )
  {
    UpdateRobot( &sensor, &controller, &leftMotor, &rightMotor, &battery );
    ReportRobot( &leftMotor, &rightMotor );
  }

  return 0;
}

//---InitLineSensor------------------------------------------------------------
// Starts the sensor at the beginning of the track.
void InitLineSensor( SLineSensor* apSensor )
{
  apSensor->cycle = 0;
}

//---InitController------------------------------------------------------------
// Starts the controller with no previous reading.
void InitController( SController* apController )
{
  apController->lastError = 0.0;
}

//---InitMotor-----------------------------------------------------------------
// Gives a motor its label and sets it stopped.
void InitMotor( SMotor* apMotor, const char* aName )
{
  apMotor->pName = aName;
  apMotor->speed = 0.0;
}

// InitBattery----------------------------------------------------------------
// Starts the battery fully charged.
void InitBattery( SBattery* apBattery )
{
  apBattery->charge = 100.0;
}

//---ReadLineSensor------------------------------------------------------------
// Returns how far the robot is off the line this cycle. Positive means the
// line is off to one side, negative the other.
int ReadLineSensor( SLineSensor* apSensor )
{
  const int Track[NumCycles] = { 2, 1, -1, -2 };

  int reading = Track[ apSensor->cycle ];
  ++apSensor->cycle;

  return reading;
}

//---ComputeSteering-----------------------------------------------------------
// Works out how hard to steer, from how far off the line the robot is and how
// quickly that is changing.
double ComputeSteering( SController* apController, int aError )
{
  double steering = 0.1 * aError + 0.05 * ( aError - apController->lastError );
  apController->lastError = aError;

  return steering;
}

//---SetMotorSpeed-------------------------------------------------------------
// Sets one motor's speed.
void SetMotorSpeed( SMotor* apMotor, double aSpeed )
{
  apMotor->speed = aSpeed;
}

//---UpdateRobot---------------------------------------------------------------
// Runs one cycle: read the sensor, work out the steering, and set both motors.
void UpdateRobot( SLineSensor* apSensor, SController* apController,
                  SMotor* apLeftMotor, SMotor* apRightMotor, SBattery* apBattery )
{
  int error = ReadLineSensor( apSensor );
  double steering = ComputeSteering( apController, error );

  // If the battery is low, slow down the robot.
  double forward = BaseSpeed;
  if( apBattery->charge < 80.0 )
  {
    forward = 0.25;  // slow down if battery is low
  }

  SetMotorSpeed( apLeftMotor, forward + steering );
  SetMotorSpeed( apRightMotor, forward - steering );

  apBattery->charge -= 1.0;  // battery drains each cycle
}

//---ReportRobot---------------------------------------------------------------
// Prints the state of both of the robot's motors.
void ReportRobot( SMotor* apLeftMotor, SMotor* apRightMotor )
{
  printf( "%s motor %g, %s motor %g\n",
          apLeftMotor->pName, apLeftMotor->speed,
          apRightMotor->pName, apRightMotor->speed );
}
