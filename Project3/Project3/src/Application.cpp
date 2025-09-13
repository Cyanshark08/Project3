#include "Application.h"

Application::Application()
	: m_State(MainAppState::MainApp),
	m_TOH()
{}

void Application::Run()
{
	while (m_State != MainAppState::Exited)
	{

	}
}

void Application::Clean()
{
	m_TOH.Clean();
}