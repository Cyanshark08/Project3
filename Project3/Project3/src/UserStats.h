#pragma once

class UserStats
{
public:
    UserStats();

    void UpdateStats(float newTime);
    void Reset();

    float GetFastestTime() const;
    float GetLongestTime() const;
    float GetAverageTime() const;
    int GetGamesPlayed() const;

private:
    float m_FastestTime;
    float m_LongestTime;
    float m_TotalTime;
    int m_GamesPlayed;
};