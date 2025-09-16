#pragma once
#include <chrono>

class Timer
{
public:
	typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;

	Timer();

	/*
	* Precondition: None
	* 
	* Postcondition: Reinitializes m_InitialTime to the current time
	*/
	time_point Reset();

	/*
	* Precondition: Timer must be initialized
	*
	* Postcondition: Returns initial time_point
	*/
	time_point GetInitialTime() const;

	/*
	* Precondition: Timer must be initialized
	*
	* Postcondition: Returns elapsed time since initial time
	*/
	float GetElapsedTime() const;
	
private:
	time_point m_InitialTime;

};

