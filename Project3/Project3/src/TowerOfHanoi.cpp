#include "TowerOfHanoi.h"
#include <sstream>
#include <algorithm>
#include "Input.h"

TowerOfHanoi::TowerOfHanoi()
	: SubApp(AppID::TowerOfHanoi),
	m_CurrentState(TOHState::Introduction)
{}

TowerOfHanoi::TowerOfHanoi(size_t p_NumOfTowers)
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
}

TOHState TowerOfHanoi::GetState() const
{
	return m_CurrentState;
}

void TowerOfHanoi::Run()
{
	while (m_CurrentState == TOHState::InProgress)
	{
		
	}

	switch (m_CurrentState)
	{
	case TOHState::Introduction:

		break;
	case TOHState::Lost:

		break;
	case TOHState::Won:

		break;
	}
}

void TowerOfHanoi::Restart()
{
	m_StackList.clear();
}

void TowerOfHanoi::Clean()
{
	m_StackList.clear();
}

void TowerOfHanoi::HandleInput(char p_Input)
{
	switch (p_Input)
	{
	}
}

void TowerOfHanoi::InitializeDisks(size_t p_NumOfTowers)
{
	m_StackList.clear();
	m_StackList.resize(p_NumOfTowers);
	for (size_t i = 0; i < p_NumOfTowers; i++)
		m_StackList[0].emplace(p_NumOfTowers - i);
}

void TowerOfHanoi::UpdateState()
{
	size_t numOfTowers = m_StackList.size();

	if (m_StackList[numOfTowers - 1].size() == numOfTowers)
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
