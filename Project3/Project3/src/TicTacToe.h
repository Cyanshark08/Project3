#pragma once
#include "SubApp.h"

#include <iostream>
#include <vector>

class TicTacToe : public SubApp
{
public:

	TicTacToe();
	TicTacToe(size_t size);
	void Run() override;
	void Restart() override;
	void Clean() override;

private:
	void setPlayerMove(size_t row, size_t column);
	void setComputerMove();
	void setSize(size_t newSize);
	void addGame();

	int checkWinner() const;
	bool isMovesLeft() const;
	int miniMax(int depth, bool isMax, int alpha, int beta);
	int evaluateBoard() const;

	int getGames() const;
	void displayBoard() const;
	void displayInfo() const;

	void HandleInput(char p_Input) override;

private:
	size_t size;
	size_t games;
	std::vector<std::vector<int32_t>> m_Board;
};

