// A clock model, with a standalone alarm clock
//
// This program models a simple clock that keeps a time in minutes and can
// advance, report, and reset it. It also provides an alarm clock, which does
// everything a clock does and additionally holds an alarm time and reports
// whether it is ringing.
//
// The alarm clock here is a brand-new, separate class. It does not inherit
// from CClock, so every part of the clock's behaviour it needs has had to be
// written out a second time.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//---CClock--------------------------------------------------------------------
// A CClock keeps a time, measured in whole minutes, and can advance it one
// minute at a time, report it, and reset it to where it started.
class CClock
{
  public:
    // Creates a clock with the given name and starting time, in minutes
    // since midnight.
    CClock( const std::string& aName, int aStartMinutes );

    // Tick advances the clock by one minute.
    void Tick();

    // GetTime returns the current time, in minutes since midnight.
    int GetTime();

    // Reset returns the clock to its starting time.
    void Reset();

    // Report prints the clock's name and current time as HH:MM.
    void Report();

  private:
    std::string mName;          // the clock's label, e.g. "Kitchen"
    int mStartMinutes;          // the time the clock was initialised to
    int mCurrentMinutes;        // current time, in minutes since midnight
};

//---AClock--------------------------------------------------------------------
// An AClock keeps a time exactly as a CClock does, and additionally holds an
// alarm time and reports whether the alarm is ringing.
//
// This class does not inherit from CClock, so everything except the two alarm
// members below is a second copy of what CClock already provides: the same
// three pieces of data, and the same four operations, including the HH:MM
// formatting inside Report. Any change to how a clock behaves would have to be
// made here as well as in CClock.
class AClock
{
  public:
    // Creates an alarm clock with the given name, starting time and alarm
    // time, all in minutes since midnight.
    AClock( const std::string& aName, int aStartMinutes, int aAlarmMinutes );

    //--repeated from CClock--
    // Tick advances the clock by one minute.
    void Tick();

    // GetTime returns the current time, in minutes since midnight.
    int GetTime();

    // Reset returns the clock to its starting time.
    void Reset();

    // Report prints the clock's name and current time as HH:MM.
    void Report();

    //--new behaviour, not in CClock--
    // SetAlarm sets the time the alarm should sound, in minutes since midnight.
    void SetAlarm( int aAlarmMinutes );

    // IsRinging reports whether the clock has reached its alarm time.
    bool IsRinging();

  private:
    std::string mName;          // repeated from CClock
    int mStartMinutes;          // repeated from CClock
    int mCurrentMinutes;        // repeated from CClock

    int mAlarmMinutes;          // the time the alarm should sound
};

//---main----------------------------------------------------------------------
// Creates one plain clock, starts it at 06:59, advances it one minute, and
// reports it. Then creates an alarm clock alongside it, sets its alarm, and
// advances it a minute at a time, reporting the time at each step, until the
// alarm rings.
int main()
{
  CClock clock( "Kitchen", 419 );    // 419 minutes = 06:59
  clock.Tick();
  clock.Report();

  AClock alarm( "Bedroom", 419, 421 );   // starts 06:59, alarm initially 07:01
  alarm.SetAlarm( 425 );                 // move the alarm later, to 07:05

  // Report the starting time, then report again after every minute until the
  // alarm sounds.
  alarm.Report();

  while( !alarm.IsRinging() )
  {
    alarm.Tick();
    alarm.Report();
  }

  std::cout << "ALARM IS RINGING, WAKEUP!!!" << std::endl;

  return 0;
}

//---CClock Implementation-----------------------------------------------------
CClock::CClock( const std::string& aName, int aStartMinutes )
  : mName( aName ),
    mStartMinutes( aStartMinutes ),
    mCurrentMinutes( aStartMinutes )
{
}
//---
void CClock::Tick()
{
  ++mCurrentMinutes;
}
//---
int CClock::GetTime()
{
  return mCurrentMinutes;
}
//---
void CClock::Reset()
{
  mCurrentMinutes = mStartMinutes;
}
//---
void CClock::Report()
{
  int hours = ( mCurrentMinutes / 60 ) % 24;
  int minutes = mCurrentMinutes % 60;
  std::cout << mName << " "
            << ( hours < 10 ? "0" : "" ) << hours << ":"
            << ( minutes < 10 ? "0" : "" ) << minutes << std::endl;
}

//---AClock Implementation-----------------------------------------------------
AClock::AClock( const std::string& aName, int aStartMinutes, int aAlarmMinutes )
  : mName( aName ),
    mStartMinutes( aStartMinutes ),
    mCurrentMinutes( aStartMinutes ),
    mAlarmMinutes( aAlarmMinutes )
{
}
//---
// Repeated from CClock::Tick
void AClock::Tick()
{
  ++mCurrentMinutes;
}
//---
// Repeated from CClock::GetTime
int AClock::GetTime()
{
  return mCurrentMinutes;
}
//---
// Repeated from CClock::Reset
void AClock::Reset()
{
  mCurrentMinutes = mStartMinutes;
}
//---
// Repeated from CClock::Report, including the HH:MM formatting
void AClock::Report()
{
  int hours = ( mCurrentMinutes / 60 ) % 24;
  int minutes = mCurrentMinutes % 60;
  std::cout << mName << " "
            << ( hours < 10 ? "0" : "" ) << hours << ":"
            << ( minutes < 10 ? "0" : "" ) << minutes << std::endl;
}
//---
void AClock::SetAlarm( int aAlarmMinutes )
{
  mAlarmMinutes = aAlarmMinutes;
}
//---
bool AClock::IsRinging()
{
  // Uses >= rather than ==, so the alarm still reports as ringing if the clock
  // is advanced past the alarm time rather than landing exactly on it.
  return mCurrentMinutes >= mAlarmMinutes;
}
