#include "UserStats.h"

UserStats::UserStats()
    : m_FastestTime(0.0f),
    m_LongestTime(0.0f),
    m_TotalTime(0.0f),
    m_GamesPlayed(0)
{}

void UserStats::UpdateStats(float newTime)
{
    if (m_GamesPlayed == 0 || newTime < m_FastestTime)
        m_FastestTime = newTime;

    if (newTime > m_LongestTime)
        m_LongestTime = newTime;

    m_TotalTime += newTime;
    m_GamesPlayed++;
}

void UserStats::Reset()
{
    m_FastestTime = 0.0f;
    m_LongestTime = 0.0f;
    m_TotalTime = 0.0f;
    m_GamesPlayed = 0;
}

float UserStats::GetFastestTime() const
{
    return m_FastestTime;
}

float UserStats::GetLongestTime() const
{
    return m_LongestTime;
}

float UserStats::GetAverageTime() const
{
    return m_GamesPlayed > 0 ? m_TotalTime / m_GamesPlayed : 0.0f;
}

int UserStats::GetGamesPlayed() const
{
    return m_GamesPlayed;
}