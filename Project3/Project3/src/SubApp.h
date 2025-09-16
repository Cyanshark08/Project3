#pragma once
#include "UserStats.h"
#include "Timer.h"

enum class AppID
{
	InvalidApp = -1,
	TicTacToe = 0,
	TowerOfHanoi = 1,
	NQueens = 2,
};

class SubApp
{
public:
	SubApp();
	SubApp(AppID p_AppID);

	/*
	* The Run() method is the main method that loops the SubApp over and over until the user exits the SubApp
	* 
	* Precondition: None
	*
	* Postcondition: Resets all specific variables relating to the implementation class to their default
	*/
	virtual void Run() = 0;

	/*
	* Precondition: None
	*
	* Postcondition: Resets all specific variables relating to the implementation class to their default
	* 
	* NOTE: Does not reset any SubApp-specific members
	*/
	virtual void Restart() = 0;

	/*
	* Precondition: None
	* 
	* Postcondition: Free memory related to SubApp entity
	*/
	virtual void Clean() = 0;

	/*
	* Precondition: None
	* 
	* Postcondition: Cleans the m_UserStatistics
	*/
	void CleanStats();
	
	/*
	* Precondition: Must be initialized
	*
	* Postcondition: Returns m_AppID
	*/
	AppID GetAppID() const;
	
	/*
	* Precondition: Must be initialized
	*
	* Postcondition: Returns m_UserStatistics
	*/
	UserStats GetUserStats() const;

	/*
	* Precondition: Must be initialized
	*
	* Postcondition: Resets App timer; Sets initial time to current time
	*/
	void BeginTimer();

	/*
	* Precondition: Timer must be initialized
	*
	* Postcondition: Gets time since BeginTimer() was last called
	*/
	void EndTimer(size_t p_NumberOfMoves);

private:
	/*
	* The Purpose of HandleInput() is to do varying things
	* based on the input provided.
	*
	* This is typically used to implement a menu for each
	* SubApp entity.
	*
	* Precondition: Pass input (Must be a valid option)
	*
	* Postcondition: Do certain instructions based on input
	*/
	virtual void HandleInput(char p_Input) = 0;
	
private:
	UserStats m_UserStatistics;
	Timer m_AppTimer;
	AppID m_AppID;

};

