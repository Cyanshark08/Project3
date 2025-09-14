#include "Application.h"

Application::Application()
	: m_State(MainAppState::MainApp),
	m_CurrentSubApp(AppID::InvalidApp),
	m_TowerOfHanoi(),
	m_TicTacToe()
{}

void Application::Run()
{
	while (m_State != MainAppState::Exited)
	{
		switch (m_State)
		{
		case MainAppState::MainApp:
			DisplayMainMenu();
			break;
		case MainAppState::SubApp:			
			switch (m_CurrentSubApp)
			{
			case AppID::TicTacToe:
				m_TicTacToe.Run();
				break;
			case AppID::TowerOfHanoi:
				m_TowerOfHanoi.Run();
				break;
			case AppID::NQueens:
				break;
			}

			m_State = MainAppState::MainApp;
			break;
		}
	}
}

void Application::Clean()
{
	m_TicTacToe.Clean();
	m_TowerOfHanoi.Clean();

}

void Application::DisplayMainMenu()
{
}
