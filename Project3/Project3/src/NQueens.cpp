#include "NQueens.h"
#include "Input.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

NQueens::NQueens()
    : SubApp(AppID::NQueens),
    m_BoardSize(4), // Changed default to 4 since 1 is valid but might be too trivial
    m_QueensPlaced(0),
    m_Moves(0)
{
    InitializeBoard(m_BoardSize);
}

void NQueens::Run()
{
    std::system("cls");
    DisplayInfo();

    // Get board size from user with valid range 1-16 excluding 2 and 3
    std::vector<int> validSizes;
    for (int i = 1; i <= 16; i++) {
        if (i != 2 && i != 3) {
            validSizes.push_back(i);
        }
    }

    std::cout << "\n\tValid board sizes: ";
    for (size_t i = 0; i < validSizes.size(); i++) {
        std::cout << validSizes[i];
        if (i < validSizes.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";

    m_BoardSize = Input::inputInteger("\n\tEnter the size of the board (1-16, excluding 2 and 3): ", 1, 16);

    // Validate that size is not 2 or 3
    while (m_BoardSize == 2 || m_BoardSize == 3) {
        std::cout << "\n\tInvalid size. Size 2 and 3 are not allowed for the N-Queens problem.\n";
        m_BoardSize = Input::inputInteger("\tPlease enter a valid size (1-16, excluding 2 and 3): ", 1, 16);
    }

    InitializeBoard(m_BoardSize);

    int games = 0;

    do
    {
        games++;
        m_Moves = 0;
        bool invalidTime = false;

        std::cout << "\n\tGame begin. Place " << m_BoardSize << " queens so that no two attack each other.\n\n";

        BeginTimer();

        while (!IsSolved())
        {
            DisplayBoard();

            // Display menu options
            std::cout << "\n\tMenu Options:\n";
            std::cout << "\t1. Place a queen\n";
            std::cout << "\t2. Remove a queen\n";
            std::cout << "\t0. Give up\n";

            int choice = Input::inputInteger("\n\tChoose an option (0-2): ", 0, 2);

            if (choice == 0)
            {
                std::cout << "\n\tYou gave up. The puzzle remains unsolved.";
                invalidTime = true;
                break;
            }

            // Get position input
            std::cout << "\n\tEnter row and column: ";
            int row, col;
            row = Input::inputInteger("\tRow: ", 1, static_cast<int>(m_BoardSize));
            col = Input::inputInteger("\tColumn: ", 1, static_cast<int>(m_BoardSize));

            // Convert to 0-based indexing
            row--;
            col--;

            if (row < m_BoardSize && col < m_BoardSize)
            {
                if (choice == 1) // Place queen
                {
                    if (m_Board[row][col] == 0)
                    {
                        // Check if the position is safe before placing a queen
                        if (IsSafe(row, col))
                        {
                            m_Board[row][col] = 1;
                            m_QueensPlaced++;
                            m_Moves++;
                            std::cout << "\n\tQueen placed successfully at position (" << row + 1 << ", " << col + 1 << ")\n";
                        }
                        else
                        {
                            std::cout << "\n\tCannot place queen here! This position is attacked by another queen.\n";
                        }
                    }
                    else
                    {
                        std::cout << "\n\tThere is already a queen at this position!\n";
                    }
                }
                else if (choice == 2) // Remove queen
                {
                    if (m_Board[row][col] == 1)
                    {
                        m_Board[row][col] = 0;
                        m_QueensPlaced--;
                        std::cout << "\n\tQueen removed successfully from position (" << row + 1 << ", " << col + 1 << ")\n";
                    }
                    else
                    {
                        std::cout << "\n\tNo queen at this position to remove!\n";
                    }
                }

                if (!IsValidConfiguration())
                {
                    std::cout << "\n\tWarning: Queens are attacking each other! This configuration is invalid.\n";
                }
            }
            else
            {
                std::cout << "\n\tInvalid position. Please enter values between 1 and " << m_BoardSize << ".\n";
            }
        }

        if (!invalidTime)
        {
            EndTimer(m_Moves);
            std::cout << "\n\tCongratulations! You solved the " << m_BoardSize << "-Queens puzzle in " << m_Moves << " moves!\n";
            DisplayBoard();
        }

        // Ask if the user wants to play again
        char again = Input::inputChar("\n\tPlay again? (Y-yes or N-no): ", 'Y', 'N');
        if (again == 'Y')
        {
            // Ask if they want to change board size
            char changeSize = Input::inputChar("\tChange board size? (Y-yes or N-no): ", 'Y', 'N');
            if (changeSize == 'Y')
            {
                m_BoardSize = Input::inputInteger("\tEnter new board size (1-16, excluding 2 and 3): ", 1, 16);

                // Validate that new size is not 2 or 3
                while (m_BoardSize == 2 || m_BoardSize == 3) {
                    std::cout << "\n\tInvalid size. Size 2 and 3 are not allowed for the N-Queens problem.\n";
                    m_BoardSize = Input::inputInteger("\tPlease enter a valid size (1-16, excluding 2 and 3): ", 1, 16);
                }
            }

            Restart();
            std::system("cls");
            std::cout << "\n\tNew Game starting.";
        }
        else
        {
            // Display game statistics
            UserStats stats = GetUserStats();

            std::cout << "\n\tGame statistics: \n";
            std::cout << "\n\t" << games << " game(s) of n-Queens were played.";

            if (stats.noTimes())
            {
                std::cout << "\n\t\tNo Game statistic collected.";
            }
            else
            {
                std::cout << "\n\t\tThe fastest time was " << stats.GetShortestTime() << " seconds in " << stats.GetShortestMoves() << " move(s)";
                std::cout << "\n\t\tThe slowest time was " << stats.GetLongestTime() << " seconds in " << stats.GetLongestMoves() << " move(s)";
                std::cout << "\n\t\tThe average time was " << stats.GetAverageTime() << " seconds";
            }
            std::cout << "\n";
            Clean();
            std::system("pause");
            break;
        }
    } while (true);

    std::system("cls");
}

void NQueens::Restart()
{
    InitializeBoard(m_BoardSize);
    m_QueensPlaced = 0;
    m_Moves = 0;
}

void NQueens::Clean()
{
    m_Board.clear();
    m_BoardSize = 0;
    m_QueensPlaced = 0;
    m_Moves = 0;
}

void NQueens::InitializeBoard(size_t boardSize)
{
    m_BoardSize = boardSize;
    m_Board.resize(m_BoardSize);
    for (size_t i = 0; i < m_BoardSize; i++)
    {
        m_Board[i].resize(m_BoardSize, 0);
    }
    m_QueensPlaced = 0;
}

void NQueens::ToggleQueen(size_t row, size_t col)
{
    if (row >= m_BoardSize || col >= m_BoardSize) return;

    if (m_Board[row][col] == 0)
    {
        // Check if the position is safe before placing a queen
        if (IsSafe(row, col))
        {
            m_Board[row][col] = 1;
            m_QueensPlaced++;
        }
        else
        {
            std::cout << "\n\tCannot place queen here! This position is attacked by another queen.\n";
        }
    }
    else
    {
        m_Board[row][col] = 0;
        m_QueensPlaced--;
    }
}

bool NQueens::IsValidConfiguration() const
{
    // Check rows
    for (size_t i = 0; i < m_BoardSize; i++)
    {
        int queenCount = 0;
        for (size_t j = 0; j < m_BoardSize; j++)
        {
            if (m_Board[i][j] == 1) queenCount++;
        }
        if (queenCount > 1) return false;
    }

    // Check columns
    for (size_t j = 0; j < m_BoardSize; j++)
    {
        int queenCount = 0;
        for (size_t i = 0; i < m_BoardSize; i++)
        {
            if (m_Board[i][j] == 1) queenCount++;
        }
        if (queenCount > 1) return false;
    }

    // Check diagonals
    for (size_t i = 0; i < m_BoardSize; i++)
    {
        for (size_t j = 0; j < m_BoardSize; j++)
        {
            if (m_Board[i][j] == 1)
            {
                // Check upper left diagonal
                for (size_t k = 1; i >= k && j >= k; k++)
                {
                    if (m_Board[i - k][j - k] == 1) return false;
                }

                // Check upper right diagonal
                for (size_t k = 1; i >= k && j + k < m_BoardSize; k++)
                {
                    if (m_Board[i - k][j + k] == 1) return false;
                }

                // Check lower left diagonal
                for (size_t k = 1; i + k < m_BoardSize && j >= k; k++)
                {
                    if (m_Board[i + k][j - k] == 1) return false;
                }

                // Check lower right diagonal
                for (size_t k = 1; i + k < m_BoardSize && j + k < m_BoardSize; k++)
                {
                    if (m_Board[i + k][j + k] == 1) return false;
                }
            }
        }
    }

    return true;
}

bool NQueens::IsSafe(size_t row, size_t col) const
{
    // Check row
    for (size_t j = 0; j < m_BoardSize; j++)
    {
        if (m_Board[row][j] == 1) return false;
    }

    // Check column
    for (size_t i = 0; i < m_BoardSize; i++)
    {
        if (m_Board[i][col] == 1) return false;
    }

    // Check upper left diagonal
    for (size_t i = row, j = col; i < m_BoardSize && j < m_BoardSize; i--, j--)
    {
        if (i >= m_BoardSize || j >= m_BoardSize) break;
        if (m_Board[i][j] == 1) return false;
    }

    // Check upper right diagonal
    for (size_t i = row, j = col; i < m_BoardSize && j < m_BoardSize; i--, j++)
    {
        if (i >= m_BoardSize || j >= m_BoardSize) break;
        if (m_Board[i][j] == 1) return false;
    }

    // Check lower left diagonal
    for (size_t i = row, j = col; i < m_BoardSize && j < m_BoardSize; i++, j--)
    {
        if (i >= m_BoardSize || j >= m_BoardSize) break;
        if (m_Board[i][j] == 1) return false;
    }

    // Check lower right diagonal
    for (size_t i = row, j = col; i < m_BoardSize && j < m_BoardSize; i++, j++)
    {
        if (i >= m_BoardSize || j >= m_BoardSize) break;
        if (m_Board[i][j] == 1) return false;
    }

    return true;
}

void NQueens::DisplayBoard() const
{
    std::stringstream ss;

    ss << "\n\tCurrent Board (" << m_QueensPlaced << "/" << m_BoardSize << " queens placed):";

    size_t rowWidth = m_BoardSize * 2 + 1;

    ss << "\n\n\t" << std::string(1, 201) << std::string(rowWidth - 2, 205) << std::string(1, 187);

    size_t rowIter{ 0 }, columnIter{ 0 };

    for (size_t i = 1; i < m_BoardSize * 2; i++)
    {
        ss << "\n\t" << std::string(1, 186);
        for (size_t j = 1; j < m_BoardSize * 2; j++)
        {
            if (i % 2)
            {
                if (j % 2)
                {
                    ss << (m_Board[rowIter][columnIter] ? 'Q' : ' ');
                    columnIter++;
                }
                else
                    ss << std::string(1, 179);

            }
            else
            {
                if (j % 2)
                    ss << '_';
                else
                    ss << std::string(1, 179);
            }

        }


        columnIter = 0;

        if (i % 2)
            rowIter++;

        ss << std::string(1, 186);
    }

    ss << "\n\t" << std::string(1, 200) << std::string(rowWidth - 2, 205) << std::string(1, 188);

    printf("%s", ss.str().c_str());
}

void NQueens::DisplayInfo() const
{
    std::cout << "\n\tThe eight queens puzzle is the problem of placing eight chess queens on an 8×8 chessboard";
    std::cout << "\n\tso that no two queens threaten each other. Thus, a solution requires that no two queens";
    std::cout << "\n\tshare the same row, column, or diagonal. The puzzle can be generalized to n queens on";
    std::cout << "\n\tan n×n board.";
    std::cout << "\n\tThis program allows you to play the n-Queens game. You can place queens on the board";
    std::cout << "\n\tby specifying their positions. The goal is to place all queens without any conflicts.";
    std::cout << "\n\tTime will be recorded for the fastest and the slowest game. Average time will";
    std::cout << "\n\tthen be calculated and displayed.";
}

void NQueens::HandleInput(char p_Input)
{
    // This method is not used in the current implementation
    // as we're handling input directly in the Run method
}

bool NQueens::IsSolved() const
{
    return m_QueensPlaced == m_BoardSize && IsValidConfiguration();
}