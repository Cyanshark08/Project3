#pragma once
#include "SubApp.h"
#include <vector>
#include <bitset>

class TicTacToe : public SubApp
{
public:
	TicTacToe();
	void Run() override;
	void Restart() override;
	void Clean() override;

	void MovePlayer();
	void MoveComputer();

private:
	std::vector<bool> m_Board;

};

