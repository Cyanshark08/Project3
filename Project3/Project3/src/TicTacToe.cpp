#include "TicTacToe.h"
#include "Input.h"


TicTacToe::TicTacToe()
	: SubApp(AppID::TicTacToe)
{
	size = 3;
	games = 0;

	m_Board.resize(size);

	// initialize the board
	for (int i = 0; i < size; i++)
		m_Board[i].resize(size);
}

TicTacToe::TicTacToe(size_t newSize)
	: SubApp(AppID::TicTacToe)
{
	size = newSize;
	games = 0;

	m_Board.resize(size);

	// initialize the board
	for (int i = 0; i < size; i++)
		m_Board[i].resize(size);
}

void TicTacToe::Run()
{
	displayInfo();
	std::cout << "\n";
	do
	{
		std::cout << "\n\t\tGame begin.\n\n";
		displayBoard();



	} while (true);
}

void TicTacToe::Restart()
{
	// reset the board
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
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
	if (row - 1 >= size)
		throw E_RowOutOfBounds(row);
	if (column - 1 >= size)
		throw E_ColumnOutOfBounds(column);
	if (m_Board[row - 1][column - 1] != 0)
		throw E_InvalidMove(row, column);

	m_Board[row - 1][column - 1] = 1;
}

void TicTacToe::setComputerMove()
{
	int bestVal = -1000;
	size_t bestRow = -1, bestCol = -1;

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (m_Board[i][j] == 0)
			{
				m_Board[i][j] = 2; // computer move
				int moveVal = miniMax(0, false); // evaluate move
				m_Board[i][j] = 0; // undo

				if (moveVal > bestVal)
				{
					bestRow = i;
					bestCol = j;
					bestVal = moveVal;
				}
			}
		}
	}

	if (bestRow != -1 && bestCol != -1)
		m_Board[bestRow][bestCol] = 2;
}

int TicTacToe::checkWinner() const
{
	// row win
	for (size_t i = 0; i < size; i++)
	{
		int first = m_Board[i][0];
		if (first == 0)
			continue;

		bool allSame = true;
		// check if any row contains the same mark
		for (size_t j = 1; j < size; j++)
		{
			if (m_Board[i][j] != first)
			{
				allSame = false;
				break;
			}
		}
		// return the winner if a row is all the same
		if (allSame)
			return first;
	}

	// column win
	for (size_t j = 0; j < size; j++)
	{
		int first = m_Board[0][j];
		if (first == 0)
			continue;

		bool allSame = true;
		// check if any column contains the same mark
		for (size_t i = 1; i < size; i++)
		{
			if (m_Board[i][j] != first)
			{
				allSame = false;
				break;
			}
		}

		// return the winner if a column is all the same
		if (allSame)
			return first;
	}

	// diagonal win (top left to bottom right)
	{
		size_t first = m_Board[0][0];
		if (first != 0)
		{
			bool allSame = true;
			// check if the diagonal line contains the same mark
			for (size_t i = 1; i < size; i++)
			{
				if (m_Board[i][i] != first)
				{
					allSame = false;
					break;
				}
			}

			// return the winner if a diagonal line is all the same
			if (allSame)
				return first;
		}
	}

	// diagonal win (top right to bottom left)
	{
		size_t first = m_Board[0][size - 1];
		if (first != 0)
		{
			bool allSame = true;
			// check if the diagonal line contains the same mark
			for (size_t i = 1; i < size; i++)
			{
				if (m_Board[i][size - 1 - i] != first)
				{
					allSame = false;
					break;
				}
			}

			// return winner if a diagonal row is all the same
			if (allSame)
				return first;
		}
	}

	// no one has won
	return 0;
}

bool TicTacToe::isMovesLeft() const
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			// return true if there is an empty spot
			if (m_Board[i][j] == 0)
				return true;
		}
	}
	// return false if no empty spots left
	return false;
}

int TicTacToe::miniMax(int depth, bool isMax)
{
	int winner = checkWinner();
	if (winner == 2) 
		return 10 - depth;   // computer wins
	if (winner == 1) 
		return depth - 10;   // player wins
	if (!isMovesLeft()) 
		return 0;         // tie

	if (isMax) // computer's move
	{
		int best = -1000;
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				// find the best move to make
				if (m_Board[i][j] == 0)
				{
					m_Board[i][j] = 2;
					best = std::max(best, miniMax(depth + 1, false));
					m_Board[i][j] = 0; // undo the move
				}
			}
		}
		return best;
	}

	else // player's move
	{
		int best = 1000;
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				// find the best move the player can make
				if (m_Board[i][j] == 0)
				{
					m_Board[i][j] = 1;
					best = std::min(best, miniMax(depth + 1, true));
					m_Board[i][j] = 0; // undo the move
				}
			}
		}
		return best;
	}
}

int TicTacToe::getGames() const
{
	return games;
}

void TicTacToe::displayBoard() const
{
	// top border
	std::cout << "\t\t" << std::string(1, 218);
	for (size_t i = 0; i < size; i++)
	{
		std::cout << std::string(3, 196);
		if (i != size - 1)
			std::cout << std::string(1, 194);
		else
			std::cout << std::string(1, 191) << "\n";
	}

	// middle squares
	for (size_t i = 0; i < size; i++)
	{
		std::cout << "\t\t";
		for (size_t j = 0; j < size; j++)
		{
			std::cout << "\t" << std::string(1, 179);

			// print x or spaces
			if (m_Board[i][j] == 0) // square is empty
				std::cout << "   ";
			else if (m_Board[i][j] == 1) // human has taken
				std::cout << " X ";
			else // computer has taken
				std::cout << " O ";
		}

		std::cout << std::string(1, 179) << "\n";
		std::cout << "\t\t";

		// separator
		if (i != size - 1)
		{
			std::cout << std::string(1, 195);
			for (size_t j = 0; j < size; j++)
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
			for (size_t j = 0; j < size; j++)
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

void TicTacToe::displayInfo() const
{
	std::cout << "\n\tTic-tac-toe (also known as Noughts and crosses or Xs and Os) is a game for two";
	std::cout << "\n\tplayers, X and O, who take turns marking the spaces in a square grid. The player who";
	std::cout << "\n\tsucceeds in placing three of their marks in a horizontal, vertical, or diagonal";
	std::cout << "\n\trow wins the game.";
	std::cout << "\n\tThis tic-tac-toe program plays against the computer. Human player, X, will always";
	std::cout << "\n\tfirst. Time will be recorded for the fastest and the slowest game. Average time will";
	std::cout << "\n\tthen be calculated and displayed.";
}

void TicTacToe::HandleInput(char p_Input)
{
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


