/* Count Up/Down Timer */
#ifndef CountUpDownTimer_h
#define CountUpDownTimer_h

#include<Arduino.h>
#define UP 1
#define DOWN 0

class CountUpDownTimer
{
  public:
    CountUpDownTimer(bool type) : _type(type)
	{ 
	  SetStopTime(0xFFFF); // 18h 12m 15s
	  time = micros();
	  Clock = 0;
	  Reset = false, Stop = false, Paused = false;
	  timeFlag = false;
	}
	
	boolean Timer()
	{
	  static unsigned long duration = 1000000; // 1 second
	  timeFlag = false;
	  if (!Stop && !Paused) // if not Stopped or Paused, run timer
	  {
		if ((_micro = micros()) - time > duration ) // check the time difference and see if 1 second has elapsed
		{
		  _type == UP? Clock++ : Clock--;
			
		  timeFlag = true;

		  if ((_type == DOWN && Clock == 0) || TimeCheck(STh, STm, STs)) // check to see if the clock is 0
			Stop = true; // If so, stop the timer
			
		  time += duration;
		  
		  if(_micro < time) 
		    time = 0;  // check to see if micros() has rolled over, if not, then increment "time" by duration
		}
	  }
	  
	  if(Paused)
	    time += micros();
		
	  return !Stop; // return the state of the timer
	}

	void ResetTimer()
	{
	  if(_type) 
	    Clock = 0;
	  else
	    SetTimer(R_clock);
	  Stop = false;
	}

	void StartTimer()
	{
	  Watch = micros();
	  Stop = false;
	  Paused = false;
	  if(_type == UP) 
	    Clock = 0;
	}

	void StopTimer()
	{
	  Stop = true;
	}

	void StopTimerAt(unsigned long hours, unsigned long minutes, unsigned long seconds)
	{
	  if (TimeCheck(hours, minutes, seconds) )
		Stop = true;
	}

	void PauseTimer()
	{
	  Paused = true;
	}

	void ResumeTimer() // You can resume the timer if you ever stop it.
	{
	  Paused = false;
	}

	void SetTimer(unsigned long hours, unsigned long minutes, unsigned long seconds)
	{
	  // This handles invalid time overflow ie 1(H), 0(M), 120(S) -> 1h, 2m, 0s
	  unsigned int _S = (seconds / 60), _M = (minutes / 60);
	  if(_S) minutes += _S;
	  if(_M) hours += _M;
	  
	  Clock = (hours * 3600) + (minutes * 60) + (seconds % 60);
	  R_clock = Clock;
	  Stop = false;
	}

	void SetTimer(unsigned long seconds)
	{
	 // StartTimer(seconds / 3600, (seconds / 3600) / 60, seconds % 60);
	  Clock = seconds;
	  R_clock = Clock;
	  Stop = false;
	}
	
	void SetStopTime(unsigned long seconds)
	{
	  STh = seconds / 3600;
	  STm = (seconds / 60) % 60;
	  STs = seconds % 60;
	}
	
	void SetStopTime(unsigned long hours, unsigned long minutes, unsigned long seconds)
	{
      STh = hours;
	  STm = minutes;
	  STs = seconds;
	}

	unsigned long ShowHours()
	{
	  return Clock / 3600;
	}

	unsigned long ShowMinutes()
	{
	  return (Clock / 60) % 60;
	}

	unsigned long ShowSeconds()
	{
	  return Clock % 60;
	}

	unsigned long ShowMilliSeconds()
	{
	  return ((_micro - Watch)/ 1000.0) + 1;
	}

	unsigned long ShowMicroSeconds()
	{
	  return (_micro - Watch) + 1;
	}

	boolean TimeHasChanged()
	{
	  return timeFlag;
	}

	boolean TimeCheck(unsigned int hours, unsigned int minutes, unsigned int seconds) // output true if timer equals requested time
	{
	  return (hours == ShowHours() && minutes == ShowMinutes() && seconds == ShowSeconds());
	}
	
    private:
	    unsigned int STh, STm, STs;
		unsigned long Watch, _micro, time;
		unsigned long Clock, R_clock;
		boolean Reset, Stop, Paused;
		volatile boolean timeFlag;
		bool _type;
};

#endif