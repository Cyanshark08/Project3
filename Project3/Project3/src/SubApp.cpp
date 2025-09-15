#include "SubApp.h"

SubApp::SubApp()
	: m_AppTimer(),
	m_UserStatistics(),
	m_AppID(AppID::InvalidApp)
{}

SubApp::SubApp(AppID p_AppID)
	: m_AppTimer(),
	m_UserStatistics(),
	m_AppID(p_AppID)
{}

AppID SubApp::GetAppID() const
{
	return m_AppID;
}

UserStats SubApp::GetUserStats() const
{
	return m_UserStatistics;
}

void SubApp::BeginTimer()
{
	m_AppTimer.Reset();
}

void SubApp::EndTimer(size_t p_NumberOfMoves)
{
	m_UserStatistics.AddTime(m_AppTimer.GetElapsedTime(), p_NumberOfMoves);
}
