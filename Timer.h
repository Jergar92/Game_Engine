#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "SDL\include\SDL.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Stop();

	double Read();
	double ReadSec() const;
private:

	bool	running;

	double ms_frecuency = 0.0;
	double second_frecuency = 0.0;

	Uint64 CounterStart = 0;
	Uint64 CounterStop = 0;

};

#endif //__TIMER_H__