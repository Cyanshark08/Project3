#pragma once
#include "SubApp.h"
#include "ExceptionInterface.h"

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

	int checkWinner() const;
	bool isMovesLeft() const;
	int miniMax(int depth, bool isMax);

	int getGames() const;
	void displayBoard() const;

	void displayInfo() const;

	void HandleInput(char p_Input) override;

// exception errors
public:
	class E_RowOutOfBounds : public ExceptionInterface
	{
	public:
		E_RowOutOfBounds(size_t row);

	private:
		std::string GetExceptionName() const override;
		std::string GetExceptionMessage() const override;

	private:
		size_t m_Row;

	};

	class E_ColumnOutOfBounds : public ExceptionInterface
	{
	public:
		E_ColumnOutOfBounds(size_t column);

	private:
		std::string GetExceptionName() const override;
		std::string GetExceptionMessage() const override;

	private:
		size_t m_Column;
	};

	class E_InvalidMove : public ExceptionInterface
	{
	public: 
		E_InvalidMove(size_t row, size_t column);

	private:
		std::string GetExceptionName() const override;
		std::string GetExceptionMessage() const override;

	private:
		size_t m_Row;
		size_t m_Column;

	};

private:
	size_t size;
	size_t games;
	std::vector<std::vector<int32_t>> m_Board;
};

