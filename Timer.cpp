// ----------------------------------------------------
// Timer.cpp
// Body for CPU Tick Timer class
// ----------------------------------------------------

#include "Timer.h"

// ---------------------------------------------
Timer::Timer()
{
	Start();
}

// ---------------------------------------------
void Timer::Start()
{
	running = true;
	// start timer
	LARGE_INTEGER time_start;
	if (!QueryPerformanceFrequency(&time_start))
		LOG("QueryPerformanceFrequency failed!");

	ms_frecuency = double(time_start.QuadPart) / 1000.0;
	second_frecuency = double(time_start.QuadPart);

	QueryPerformanceCounter(&time_start);
	CounterStart = time_start.QuadPart;
}

// ---------------------------------------------
void Timer::Stop()
{
	running = false;
	// stop timer
	LARGE_INTEGER time_stop;
	QueryPerformanceCounter(&time_stop);
	CounterStop = time_stop.QuadPart;

}

// ---------------------------------------------
double Timer::Read()
{
	if(running == true)
	{
		LARGE_INTEGER current_time;
		QueryPerformanceCounter(&current_time);
		return double(current_time.QuadPart - CounterStart) / ms_frecuency;
	}
	else
	{
		return CounterStop - CounterStart;
	}
}
double Timer::ReadSec() const
{
	LARGE_INTEGER current_time;
	QueryPerformanceCounter(&current_time);
	return double(current_time.QuadPart - CounterStart) / second_frecuency;
}


