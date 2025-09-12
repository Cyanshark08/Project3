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
	virtual void Run() = 0;
	virtual void Restart() = 0;
	virtual void Clean() = 0;
	
	AppID GetAppID() const;
	
	UserStats GetUserStats() const;
	
private:
	UserStats m_UserStatistics;
	Timer m_AppTimer;
	AppID m_AppID;

};

