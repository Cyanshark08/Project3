#include "Application.h"
#include <string>
#include "Input.h"

Application::Application()
	: m_State(MainAppState::MainApp),
	m_CurrentSubApp(AppID::InvalidApp),
	m_TowerOfHanoi(),
	m_TicTacToe()
	m_NQueens() 
{}

void Application::Run()
{
	while (m_State != MainAppState::Exited)
	{
		switch (m_State)
		{
		case MainAppState::MainApp:
			DisplayMainMenu();
			QueryState();
			break;
		case MainAppState::SubApp:			
			switch (m_CurrentSubApp)
			{
			case AppID::TicTacToe:
				m_TicTacToe.Run();
				m_TicTacToe.CleanStats();
				break;
			case AppID::TowerOfHanoi:
				m_TowerOfHanoi.Run();
				m_TowerOfHanoi.CleanStats();
				break;
			case AppID::NQueens:
				m_NQueens.Run();
				m_NQueens.Cleanstats();
				break;
			}

			m_State = MainAppState::MainApp;
			m_CurrentSubApp = AppID::InvalidApp;
			break;
		}
	}
}

void Application::Clean()
{
	m_TicTacToe.Clean();
	m_TowerOfHanoi.Clean();
	m_NQueens.Clean();

}

void Application::DisplayMainMenu()
{
	puts("\n\tCMPR131 Chapter 3 - Games Applications using Container by Andrew, Jaime, & Landon");
	puts(std::string(110, 205).c_str());
	puts("\t1 > Tic - Tac - Toe");
	puts("\t2 > Tower of Hanoi");
	puts("\t3 > n - Queens");
	puts(std::string(110, 196).c_str());
	puts("\t0. Exit");
	puts(std::string(110, 205).c_str());
}

void Application::QueryState()
{
	char choice = Input::inputChar("\n\tOption: ", "1230");
	switch (choice)
	{
	case '1':
		m_State = MainAppState::SubApp;
		m_CurrentSubApp = AppID::TicTacToe;
		break;
	case '2':
		m_State = MainAppState::SubApp;
		m_CurrentSubApp = AppID::TowerOfHanoi;
		break;
	case '3':
		m_State = MainAppState::SubApp;
		m_CurrentSubApp = AppID::NQueens;
		break;
	case '0':
		m_State = MainAppState::Exited;
		break;
	}
}
