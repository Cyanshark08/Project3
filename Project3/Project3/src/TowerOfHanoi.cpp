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
}

TOHState TowerOfHanoi::GetState() const
{
	return m_CurrentState;
}

void TowerOfHanoi::Run()
{
	if (m_CurrentState == TOHState::Introduction)
	{

	}

	while (m_CurrentState == TOHState::InProgress)
	{

	}
}

void TowerOfHanoi::Restart()
{
}

void TowerOfHanoi::Clean()
{
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
