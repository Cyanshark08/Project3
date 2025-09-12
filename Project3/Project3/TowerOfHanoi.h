#pragma once
#include <stack>
#include <vector>
#include "Disk.h"

enum class TOHState
{
	Undecided,
	Lost,
	Won
};

class TowerOfHanoi
{
public:
	TowerOfHanoi(size_t p_NumOfTowers);
	void MoveDisk(size_t p_OldTower, size_t p_NewTower);
	TOHState GetState() const;

public:
	class E_InvalidMovement
	{

	};

private:
	void UpdateState();

private:
	std::vector<std::stack<Disk>> m_Stack;
	TOHState m_CurrentState;
	size_t m_MoveCount;

};

