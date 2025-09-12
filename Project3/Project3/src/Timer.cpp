#include "Timer.h"

Timer::Timer()
{
    m_InitialTime = std::chrono::high_resolution_clock::now();
}

Timer::time_point Timer::Reset()
{
    m_InitialTime = std::chrono::high_resolution_clock::now();
    return m_InitialTime;
}

Timer::time_point Timer::GetInitialTime() const
{
    return m_InitialTime;
}

float Timer::GetElapsedTime() const
{
    std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - m_InitialTime;
    return duration.count();
}
