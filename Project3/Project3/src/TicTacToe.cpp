#include "TicTacToe.h"


TicTacToe::TicTacToe()
	: SubApp(AppID::TicTacToe),
	size(3), // default 3x3 board
	m_Board(size, std::vector<int>(size, 0))
{	
}

TicTacToe::TicTacToe(size_t newSize)
	: SubApp(AppID::TicTacToe),
	size(newSize),
	m_Board(newSize, std::vector<int>(newSize, 0))
{
}

void TicTacToe::Run()
{

}

void TicTacToe::Restart()
{
	// reset the board
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			m_Board[i][j] = 0;
		}
	}
}

void TicTacToe::Clean()
{
	size = 0;
	m_Board.clear();
}

void TicTacToe::setPlayerMove(size_t row, size_t column)
{
	// throw exception errors if invalid row/ column/ move
	if (row >= size)
		throw E_RowOutOfBounds(row);
	if (column >= size)
		throw E_ColumnOutOfBounds(column);
	if (m_Board[row][column] != 0)
		throw E_InvalidMove(row, column);

	m_Board[row][column] = 1;
}

void TicTacToe::setComputerMove()
{

}

void TicTacToe::displayBoard() const
{
	// top border
	std::cout << std::string(1, 218);
	for (int i = 0; i < size; i++)
	{
		std::cout << std::string(3, 196);
		if (i != size - 1)
			std::cout << std::string(1, 194);
		else
			std::cout << std::string(1, 191) << "\n";
	}

	// middle squares
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << std::string(1, 179);

			// print x or spaces
			if (m_Board[i][j] == 0) // square is empty
				std::cout << "   ";
			else if (m_Board[i][j] == 1) // human has taken
				std::cout << " X ";
			else // computer has taken
				std::cout << " O ";
		}

		std::cout << std::string(1, 179) << "\n";

		// separator
		if (i != size - 1)
		{
			std::cout << std::string(1, 195);
			for (int j = 0; j < size; j++)
			{
				std::cout << std::string(3, 196);
				if (j != size - 1)
					std::cout << std::string(1, 197);
				else
					std::cout << std::string(1, 180);
			}
			std::cout << "\n";
		}

		// bottom border
		else
		{
			std::cout << std::string(1, 192);
			for (int j = 0; j < size; j++)
			{
				std::cout << std::string(3, 196);
				if (j != size - 1)
					std::cout << std::string(1, 193);
				else
					std::cout << std::string(1, 217);

			}
			std::cout << "\n";
		}
	}
}


// E_RowOutOfBounds
TicTacToe::E_RowOutOfBounds::E_RowOutOfBounds(size_t row)
{
	m_Row = row;
}

inline std::string TicTacToe::E_RowOutOfBounds::GetExceptionName() const
{
	return "Row out of bounds";
}

inline std::string TicTacToe::E_RowOutOfBounds::GetExceptionMessage() const
{
	return "Row [" + std::to_string(m_Row) + "] out of bounds.";
}


// E_ColumnOutOfBounds
TicTacToe::E_ColumnOutOfBounds::E_ColumnOutOfBounds(size_t column)
{
	m_Column = column;
}

inline std::string TicTacToe::E_ColumnOutOfBounds::GetExceptionName() const
{
	return "Column out of bounds";
}

inline std::string TicTacToe::E_ColumnOutOfBounds::GetExceptionMessage() const
{
	return "Column [" + std::to_string(m_Column) + "] out of bounds.";
}

// E_InvalidMove
TicTacToe::E_InvalidMove::E_InvalidMove(size_t row, size_t column)
{
	m_Row = row;
	m_Column = column;
}

inline std::string TicTacToe::E_InvalidMove::GetExceptionName() const
{
	return "Invalid move. Square has already been taken";
}

inline std::string TicTacToe::E_InvalidMove::GetExceptionMessage() const
{
	return "Area [" + std::to_string(m_Row) + "][" + std::to_string(m_Column) + "] has already been taken.";
}


