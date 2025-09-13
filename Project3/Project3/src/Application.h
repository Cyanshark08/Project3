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
	MainAppState m_State;
	TowerOfHanoi m_TOH;

};

