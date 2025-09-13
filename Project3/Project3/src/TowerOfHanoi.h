#pragma once
#include <stack>
#include <vector>
#include <string>
#include "ExceptionInterface.h"
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
	class E_IllegalMove : public ExceptionInterface
	{
	public:
		E_IllegalMove();

	private:
		std::string GetExceptionName() const override;
		std::string GetExceptionMessage() const override;

	private:
		size_t m_InitialTower, m_FinalTower;

	};

private:
	void UpdateState();

private:
	std::vector<std::stack<Disk>> m_Stack;
	TOHState m_CurrentState;
	size_t m_MoveCount;

};

