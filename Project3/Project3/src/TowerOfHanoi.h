#pragma once
#include <stack>
#include <array>
#include <string>
#include "ExceptionInterface.h"
#include "Disk.h"
#include "SubApp.h"

enum class TOHState
{
	Introduction,
	InProgress,
	Exited,
	Won
};

class TowerOfHanoi : public SubApp
{
public:
	TowerOfHanoi();

	/*
	* Precondition: start tower must not be empty; end tower top disk must be of lower size than the start tower disk.
	* 
	* Postcondition: moves the disk on top of start tower to end tower
	*/
	void MoveDisk(size_t p_OldTower, size_t p_NewTower);

	/*
	* Precondition: None
	*
	* Postcondition: Sets the number of disks
	*/
	void SetNumberOfDisks(size_t p_NumOfDisks);

	/*
	* Precondition: None
	*
	* Postcondition: Returns state
	*/
	TOHState GetState() const;

	/*
	* Precondition: Game must be initialized and in a valid state
	*
	* Postcondition: Displays Tower Of Hanoi stacks
	*/
	void DisplayGame() const;

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

	class E_EmptyStack : public ExceptionInterface
	{
	public:
		E_EmptyStack(size_t p_StackNum);

	private:
		std::string GetExceptionName() const override;
		std::string GetExceptionMessage() const override;

	private:
		size_t m_StackNum;
	};

private:
	void InitializeDisks();
	void UpdateState();

	void HandleInput(char p_Input) override;

private:
	constexpr static const uint8_t s_NumberOfTowers = 3ui8;

private:
	std::array<std::stack<Disk>, 3> m_StackList;
	TOHState m_CurrentState;
	size_t m_MoveCount;
	size_t m_NumberOfDisks;

};

