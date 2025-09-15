#include "UserStats.h"
#include <algorithm>

float UserStats::GetLongestTime() const
{
    return m_Times[m_Times.size() - 1];
}

float UserStats::GetShortestTime() const
{
    return m_Times[0];
}

float UserStats::GetAverageTime() const
{
    float sum = 0.f;
    for (float time : m_Times)
        sum += time;

    return sum / (float) m_Times.size();
}

size_t UserStats::GetLongestMoves() const
{
    return m_LongestMoves;
}

size_t UserStats::GetShortestMoves() const
{
    return m_ShortestMoves;
}

void UserStats::AddTime(float p_Duration, size_t p_NumberOfMoves)
{
    if(m_Times.size() != 0)
    {
        std::sort(m_Times.begin(), m_Times.end());

        if (p_Duration < m_Times[0])
            m_ShortestMoves = p_NumberOfMoves;

        if (p_Duration > m_Times[m_Times.size() - 1])
            m_LongestMoves = p_NumberOfMoves;
    }
    else
    {
        m_ShortestMoves = p_NumberOfMoves;
        m_LongestMoves = p_NumberOfMoves;
    }

    m_Times.push_back(p_Duration);
}
