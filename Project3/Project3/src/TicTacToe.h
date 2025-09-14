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

	void setPlayerMove(size_t row, size_t column);
	void setComputerMove();
	void displayBoard() const;

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
	std::vector<std::vector<int32_t>> m_Board;
};

