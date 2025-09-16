#pragma once
#include <vector>

class UserStats
{
public:
	/*
	* Precondition: m_Times must not be empty
	* 
	* Postcondition: Returns the longest time
	*/
	float GetLongestTime() const;

	/*
	* Precondition: m_Times must not be empty
	*
	* Postcondition: Returns the shortest time
	*/
	float GetShortestTime() const;

	/*
	* Precondition: m_Times must not be empty
	*
	* Postcondition: Returns the average time
	*/
	float GetAverageTime() const;

	/*
	* Precondition: m_Times must not be empty
	*
	* Postcondition: Returns the amount of moves during the longest time
	*/
	size_t GetLongestMoves() const;

	/*
	* Precondition: m_Times must not be empty
	*
	* Postcondition: Returns the amount of moves during the shortest time
	*/
	size_t GetShortestMoves() const;

	/*
	* Precondition: m_Times must not be empty
	*
	* Postcondition: Returns the size of m_Times
	*/
	size_t GetNumOfGamesPlayed() const;

	/*
	* Precondition: None
	*
	* Postcondition: Adds a time to m_Times
	*/
	void AddTime(float p_Duration, size_t p_NumberOfMoves);

	/*
	* Precondition: None
	*
	* Postcondition: Returns true if m_Times is empty
	*/
	bool noTimes() const;

	/*
	* Precondition: None
	*
	* Postcondition: Clears m_Times 
	*/
	void Clean();

private:

	std::vector<float> m_Times;

	size_t m_ShortestMoves;
	size_t m_LongestMoves;

};

