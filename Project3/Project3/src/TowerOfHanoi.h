#pragma once
#include <stack>
#include <vector>
#include <string>
#include "ExceptionInterface.h"
#include "Disk.h"
#include "SubApp.h"

enum class TOHState
{
	Undecided,
	Lost,
	Won
};

class TowerOfHanoi : public SubApp
{
public:
	TowerOfHanoi();
	TowerOfHanoi(size_t p_NumOfTowers);
	void MoveDisk(size_t p_OldTower, size_t p_NewTower);
	TOHState GetState() const;

	void Run() override;
	void Restart() override;
	void Clean() override;

public:
	class E_IllegalMove : public ExceptionInterface
	{
	public:
		E_IllegalMove(size_t p_InitialTower, size_t p_FinalTower, size_t p_InitialTowerDisk, size_t p_FinalTowerDisk);

	private:
		std::string GetExceptionName() const override;
		std::string GetExceptionMessage() const override;

	private:
		size_t m_InitialTower, m_FinalTower;
		size_t m_InitialTowerDisk, m_FinalTowerDisk;

	};

private:
	void InitializeDisks(size_t p_NumOfTowers);
	void UpdateState();

	void HandleInput(char p_Input) override;

private:
	std::vector<std::stack<Disk>> m_StackList;
	TOHState m_CurrentState;
	size_t m_MoveCount;

};

