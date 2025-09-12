#pragma once
#include <chrono>

class Timer
{
public:
	typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;

	Timer();
	time_point Reset();

	time_point GetInitialTime() const;
	float GetElapsedTime() const;
	
private:
	time_point m_InitialTime;

};

