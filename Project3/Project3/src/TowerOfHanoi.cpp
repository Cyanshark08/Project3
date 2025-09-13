#include "TowerOfHanoi.h"
#include <sstream>

TowerOfHanoi::TowerOfHanoi(size_t p_NumOfTowers)
{
}

void TowerOfHanoi::MoveDisk(size_t p_OldTower, size_t p_NewTower)
{
}

TOHState TowerOfHanoi::GetState() const
{
	return m_CurrentState;
}

void TowerOfHanoi::UpdateState()
{
	//TODO: 
}

std::string TowerOfHanoi::E_IllegalMove::GetExceptionName() const
{
	return "Illegal Move";
}

std::string TowerOfHanoi::E_IllegalMove::GetExceptionMessage() const
{
	std::stringstream ss;
	ss << "Moving " << m_InitialTower <<
	return "";
}
