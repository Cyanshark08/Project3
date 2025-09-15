#include "TowerOfHanoi.h"
#include <sstream>
#include <algorithm>
#include "Input.h"

TowerOfHanoi::TowerOfHanoi()
	: SubApp(AppID::TowerOfHanoi),
	m_CurrentState(TOHState::Introduction)
{}

void TowerOfHanoi::MoveDisk(size_t p_OldTower, size_t p_NewTower)
{
	Disk newTopDisk = m_StackList[p_OldTower - 1].top();
	Disk oldTopDisk = m_StackList[p_NewTower - 1].top();

	if (newTopDisk > oldTopDisk)
		throw E_IllegalMove(
			p_OldTower, 
			p_NewTower, 
			m_StackList[p_OldTower - 1].top().GetDiskNumber(), 
			m_StackList[p_NewTower - 1].top().GetDiskNumber());

	
	m_StackList[p_OldTower - 1].pop();
	m_StackList[p_NewTower - 1].push(newTopDisk);

	m_MoveCount++;
}

TOHState TowerOfHanoi::GetState() const
{
	return m_CurrentState;
}

void TowerOfHanoi::DisplayGame() const
{
}

void TowerOfHanoi::Run()
{
	while (m_CurrentState == TOHState::InProgress)
	{
		DisplayGame();
		try
		{
			MoveDisk(Input::inputInteger("", true), Input::inputInteger("", true));
		}
		catch(const ExceptionInterface& e)
		{
			puts(e.Message().c_str());
		}
	}

	switch (m_CurrentState)
	{
	case TOHState::Introduction:

		m_CurrentState = TOHState::InProgress;
		break;
	case TOHState::Lost:

		break;
	case TOHState::Won:

		break;
	}
}

void TowerOfHanoi::Restart()
{
	this->Clean();
}

void TowerOfHanoi::Clean()
{
	for (size_t i = 0; i < s_NumberOfTowers; i++)
		m_StackList[i]._Get_container().~deque();
}

void TowerOfHanoi::HandleInput(char p_Input)
{
	switch (p_Input)
	{
	}
}

void TowerOfHanoi::InitializeDisks()
{
	for (size_t i = 0; i < s_NumberOfTowers; i++)
		m_StackList[0].emplace(s_NumberOfTowers - i);
}

void TowerOfHanoi::UpdateState()
{
	if (m_StackList[s_NumberOfTowers - 1].size() == s_NumberOfTowers)
		m_CurrentState = TOHState::Won;
}

TowerOfHanoi::E_IllegalMove::E_IllegalMove(size_t p_InitialTower, size_t p_FinalTower, size_t p_InitialTowerDisk, size_t p_FinalTowerDisk)
	: m_InitialTower(p_InitialTower),
	m_FinalTower(p_FinalTower),
	m_InitialTowerDisk(p_InitialTowerDisk),
	m_FinalTowerDisk(p_InitialTowerDisk)
{}

std::string TowerOfHanoi::E_IllegalMove::GetExceptionName() const
{
	return "Illegal Move";
}

std::string TowerOfHanoi::E_IllegalMove::GetExceptionMessage() const
{
	std::stringstream ss;
	ss << "Cannot move disk #" << m_InitialTowerDisk << " from Tower #" << m_InitialTower << " to Tower #" << m_FinalTower;
	return ss.str();
}
