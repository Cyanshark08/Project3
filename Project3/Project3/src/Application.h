#pragma once
#include "SubApp.h"
#include "TowerOfHanoi.h"
#include "TicTacToe.h"
#include <memory>

enum class MainAppState
{
	MainApp,
	SubApp,
	Exited
};

class Application
{
public:

	Application();

	void Run();

	void Clean();

private:
	void DisplayMainMenu();
	void QueryState();

private:
	MainAppState m_State;
	AppID m_CurrentSubApp;
	TowerOfHanoi m_TowerOfHanoi;
	TicTacToe m_TicTacToe;

};

