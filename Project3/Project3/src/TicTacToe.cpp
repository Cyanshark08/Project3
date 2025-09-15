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
	std::system("cls");

	// display tic tac toe information
	displayInfo();
	std::cout << "\n";

	// initialize the board size
	size_t newSize = Input::inputInteger("\n\tEnter the size of the board (larger size = longer computer time): ", true);
	setSize(newSize);
	m_Board.assign(size, std::vector<int>(size, 0));

	std::cout << "\n";
	do
	{
		addGame();
		std::cout << "\n\tGame begin.\n\n";
		displayBoard();
		do
		{

			std::cout << "\n\tHUMAN Moves:";

			// ask for the player's move
			int bound = size;
			int row = Input::inputInteger("\n\t\tEnter the board's row (1.." + std::to_string(size) + ") or 0 to forfeit: ", 0, bound);
			if (row == 0)
			{
				std::cout << "\n\tYou forfeited the game. Therefore, Dumb AI has won.";
				break;
			}
			int column = Input::inputInteger("\t\tEnter the board's column (1.." + std::to_string(size) + ") or 0 to forfeit: ", 0, bound);
			if (column == 0)
			{
				std::cout << "\n\tYou forfeited the game. Therefore, Computer has won.";
				break;
			}

			// check if there are moves left
			if (isMovesLeft() && m_Board[row - 1][column - 1] == 0)
			{
				setPlayerMove(row, column);
				std::cout << "\n";
				displayBoard();
			}

			// tie if no moves left and no winner
			else if (!isMovesLeft() && checkWinner() == 0)
			{
				std::cout << "\n\tTie.";
				break;
			}
			// player inputted an area already taken
			else
			{
				std::cout << "\n\tERROR: Illegal Move. Square is already taken. Please re-enter move.\n";
				continue;
			}

			// check if the player has won
			if (checkWinner() == 1)
			{
				std::cout << "\n\tHUMAN has won.";
				break;
			}

			// check if there are moves left
			if (isMovesLeft())
			{
				std::cout << "\n\tCOMPUTER Moves:";
				setComputerMove();
				std::cout << "\n";
				displayBoard();
			}

			// tie if no moves left and no winner
			else if (!isMovesLeft() && checkWinner() == 0)
			{
				std::cout << "\n\tTie.";
				break;
			}

			// check if the computer has won
			if (checkWinner() == 2)
			{
				std::cout << "\n\tCOMPUTER has won.";
				break;
			}
		} while (true);

		// ask if the user wants to play again
		char again = Input::inputChar("\n\tPlay again? (Y-yes or N-no): ", 'Y', 'N');
		if (again == 'Y')
			Restart();
		else
		{
			// display game statistics
			std::cout << "\n\tGame statistics: ";
			std::cout << "\n\t\t" << getGames() << " game(s) of Tic-Tac-Toe were played.\n\n";
			Clean();
			std::system("pause");
			break;
		}
		std::cout << "\n";
	} while (true);
	std::system("cls");
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
	games = 0;
	m_Board.clear();
}

void TicTacToe::setPlayerMove(size_t row, size_t column)
{
	m_Board[row - 1][column - 1] = 1;
}

void TicTacToe::setComputerMove()
{
	int bestScore = -1000;
	int bestRow = -1, bestCol = -1;

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (m_Board[i][j] == 0) // empty
			{
				// try move
				m_Board[i][j] = 2;
				int moveScore = miniMax(0, false, -1000, 1000);

				// undo move
				m_Board[i][j] = 0;

				// pick best move
				if (moveScore > bestScore)
				{
					bestScore = moveScore;
					bestRow = i;
					bestCol = j;
				}
			}
		}
	}

	// Make the best move
	if (bestRow != -1 && bestCol != -1)
		m_Board[bestRow][bestCol] = 2;
}

void TicTacToe::setSize(size_t newSize)
{
	size = newSize;
}

void TicTacToe::addGame()
{
	games += 1;
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

int TicTacToe::miniMax(int depth, bool isMax, int alpha, int beta)
{
	int winner = checkWinner();
	if (winner == 2) return 100 - depth;
	if (winner == 1) return depth - 100;
	if (!isMovesLeft()) return 0;

	if (depth >= 5)
		return evaluateBoard();

	// computer move
	if (isMax) 
	{
		int best = -1000;
		for (size_t i = 0; i < size; i++) 
		{
			for (size_t j = 0; j < size; j++) 
			{
				if (m_Board[i][j] == 0) 
				{
					m_Board[i][j] = 2;
					best = std::max(best, miniMax(depth + 1, false, alpha, beta));
					m_Board[i][j] = 0;
					alpha = std::max(alpha, best);
					if (beta <= alpha) 
						return best;
				}
			}
		}
		return best;
	}

	// computer move
	else
	{
		int best = 1000;
		for (size_t i = 0; i < size; i++) 
		{
			for (size_t j = 0; j < size; j++) 
			{
				if (m_Board[i][j] == 0) 
				{
					m_Board[i][j] = 1;
					best = std::min(best, miniMax(depth + 1, true, alpha, beta));
					m_Board[i][j] = 0;
					beta = std::min(beta, best);
					if (beta <= alpha) 
						return best;
				}
			}
		}
		return best;
	}
}

int TicTacToe::evaluateBoard() const
{
	int winner = checkWinner();
	if (winner == 2) 
		return 100;
	if (winner == 1) 
		return -100;

	int score = 0;

	// Check rows
	for (size_t i = 0; i < size; i++) 
	{
		int playerCount = 0, compCount = 0;
		for (size_t j = 0; j < size; j++) 
		{
			if (m_Board[i][j] == 1) 
				playerCount++;
			else if (m_Board[i][j] == 2) 
				compCount++;
		}
		if (playerCount == 0 && compCount > 0) 
			score += compCount * compCount;
		if (compCount == 0 && playerCount > 0) 
			score -= playerCount * playerCount;
	}

	// Check columns
	for (size_t j = 0; j < size; j++) 
	{
		int playerCount = 0, compCount = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (m_Board[i][j] == 1) playerCount++;
			else if (m_Board[i][j] == 2) compCount++;
		}
		if (playerCount == 0 && compCount > 0) 
			score += compCount * compCount;
		if (compCount == 0 && playerCount > 0) 
			score -= playerCount * playerCount;
	}

	// Check diagonals
	int playerCount = 0, compCount = 0;
	for (size_t i = 0; i < size; i++) 
	{
		if (m_Board[i][i] == 1) playerCount++;
		else if (m_Board[i][i] == 2) compCount++;
	}
	if (playerCount == 0 && compCount > 0) 
		score += compCount * compCount;
	if (compCount == 0 && playerCount > 0) 
		score -= playerCount * playerCount;

	playerCount = compCount = 0;
	for (size_t i = 0; i < size; i++) 
	{
		if (m_Board[i][size - i - 1] == 1)
			playerCount++;
		else if (m_Board[i][size - i - 1] == 2) 
			compCount++;
	}
	if (playerCount == 0 && compCount > 0) 
		score += compCount * compCount;
	if (compCount == 0 && playerCount > 0) 
		score -= playerCount * playerCount;

	return score;
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