#pragma once
#include <vector>

class UserStats
{
public:
	float GetLongestTime() const;
	float GetShortestTime() const;
	float GetAverageTime() const;

	size_t GetLongestMoves() const;
	size_t GetShortestMoves() const;

	size_t GetNumOfGamesPlayed() const;

	void AddTime(float p_Duration, size_t p_NumberOfMoves);

	bool noTimes() const;
	void Clean();

private:

	std::vector<float> m_Times;

	size_t m_ShortestMoves;
	size_t m_LongestMoves;

};

