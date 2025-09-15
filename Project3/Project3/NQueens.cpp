#include "NQueens.h"
#include "Input.h"
#include <iostream>
#include <iomanip>
#include <chrono>

NQueens::NQueens()
    : SubApp(AppID::NQueens),
    m_BoardSize(8),
    m_SolutionCount(0),
    m_TotalGames(0),
    m_FastestSolution(INT_MAX),
    m_SlowestSolution(0),
    m_AverageTime(0.0f),
    m_AutoSolve(false)
{
    ResetBoard();
}

void NQueens::Run()
{
    std::system("cls");
    DisplayInfo();

    char choice;
    do
    {
        DisplayMenu();
        choice = Input::inputChar("\n\tOption: ", "12340");

        switch (choice)
        {
        case '1': // Play game
        {
            m_TotalGames++;
            m_BoardSize = Input::inputInteger("\n\tEnter board size (4-12 recommended): ", 4, 20);
            ResetBoard();

            auto start = std::chrono::high_resolution_clock::now();

            if (m_AutoSolve)
            {
                m_SolutionCount = 0;
                SolveAllSolutions(0);
                std::cout << "\n\tTotal solutions for " << m_BoardSize << " queens: " << m_SolutionCount << std::endl;
            }
            else
            {
                // Manual play implementation
                int queensPlaced = 0;
                while (queensPlaced < m_BoardSize)
                {
                    DisplayBoard();
                    int row = Input::inputInteger("\n\tEnter row (1-" + std::to_string(m_BoardSize) + "): ", 1, m_BoardSize);
                    int col = Input::inputInteger("\tEnter column (1-" + std::to_string(m_BoardSize) + "): ", 1, m_BoardSize);

                    if (IsSafe(row - 1, col - 1))
                    {
                        m_Board[row - 1][col - 1] = true;
                        queensPlaced++;
                    }
                    else
                    {
                        std::cout << "\n\tInvalid move! Queen would be attacked. Try again.\n";
                    }
                }

                DisplayBoard();
                std::cout << "\n\tCongratulations! You've placed all queens safely!\n";
            }

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;
            float timeTaken = duration.count();

            // Update statistics
            if (timeTaken < m_FastestSolution) m_FastestSolution = timeTaken;
            if (timeTaken > m_SlowestSolution) m_SlowestSolution = timeTaken;
            m_AverageTime = ((m_AverageTime * (m_TotalGames - 1)) + timeTaken) / m_TotalGames;

            break;
        }
        case '2': // Toggle auto-solve
            m_AutoSolve = !m_AutoSolve;
            std::cout << "\n\tAuto-solve " << (m_AutoSolve ? "ENABLED" : "DISABLED") << std::endl;
            break;
        case '3': // Display statistics
            DisplayStatistics();
            break;
        case '4': // Display current board
            DisplayBoard();
            break;
        case '0': // Return to main menu
            std::cout << "\n\tReturning to main menu...\n";
            break;
        }

        if (choice != '0')
        {
            std::system("pause");
            std::system("cls");
        }

    } while (choice != '0');
}

void NQueens::Restart()
{
    ResetBoard();
    m_SolutionCount = 0;
}

void NQueens::Clean()
{
    m_Board.clear();
    m_BoardSize = 8;
    m_SolutionCount = 0;
}

void NQueens::HandleInput(char p_Input)
{
    // Implementation for handling specific input if needed
}

void NQueens::DisplayBoard() const
{
    std::cout << "\n\t";
    for (int i = 0; i < m_BoardSize; i++)
    {
        std::cout << " " << i + 1;
    }
    std::cout << "\n\t";

    for (int i = 0; i < m_BoardSize * 2 + 1; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (int i = 0; i < m_BoardSize; i++)
    {
        std::cout << "\t" << i + 1 << "|";
        for (int j = 0; j < m_BoardSize; j++)
        {
            std::cout << (m_Board[i][j] ? "Q" : ".") << " ";
        }
        std::cout << std::endl;
    }
}

void NQueens::DisplayInfo() const
{
    std::cout << "\n\tN-Queens Problem";
    std::cout << "\n\tThe eight queens puzzle is the problem of placing eight chess queens on an 8×8";
    std::cout << "\n\tchessboard so that no two queens threaten each other. Thus, a solution requires";
    std::cout << "\n\tthat no two queens share the same row, column, or diagonal.";
    std::cout << "\n\tThis program allows you to solve the puzzle manually or automatically for any";
    std::cout << "\n\tboard size N x N.";
    std::cout << "\n";
}

bool NQueens::IsSafe(int row, int col) const
{
    // Check row on left side
    for (int i = 0; i < col; i++)
        if (m_Board[row][i])
            return false;

    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (m_Board[i][j])
            return false;

    // Check lower diagonal on left side
    for (int i = row, j = col; j >= 0 && i < m_BoardSize; i++, j--)
        if (m_Board[i][j])
            return false;

    return true;
}

bool NQueens::Solve(int col)
{
    if (col >= m_BoardSize)
        return true;

    for (int i = 0; i < m_BoardSize; i++)
    {
        if (IsSafe(i, col))
        {
            m_Board[i][col] = true;

            if (Solve(col + 1))
                return true;

            m_Board[i][col] = false;
        }
    }

    return false;
}

bool NQueens::SolveAllSolutions(int col)
{
    if (col == m_BoardSize)
    {
        m_SolutionCount++;
        return true;
    }

    bool res = false;
    for (int i = 0; i < m_BoardSize; i++)
    {
        if (IsSafe(i, col))
        {
            m_Board[i][col] = true;

            res = SolveAllSolutions(col + 1) || res;

            m_Board[i][col] = false;
        }
    }

    return res;
}

void NQueens::CountSolutions()
{
    m_SolutionCount = 0;
    SolveAllSolutions(0);
}

void NQueens::ResetBoard()
{
    m_Board.resize(m_BoardSize);
    for (int i = 0; i < m_BoardSize; i++)
    {
        m_Board[i].resize(m_BoardSize, false);
    }
}

void NQueens::DisplayStatistics() const
{
    std::cout << "\n\tN-Queens Game Statistics";
    std::cout << "\n\t=========================";
    std::cout << "\n\tTotal games played: " << m_TotalGames;
    std::cout << "\n\tFastest solution: " << std::fixed << std::setprecision(2) << m_FastestSolution << " seconds";
    std::cout << "\n\tSlowest solution: " << std::fixed << std::setprecision(2) << m_SlowestSolution << " seconds";
    std::cout << "\n\tAverage time: " << std::fixed << std::setprecision(2) << m_AverageTime << " seconds";
    std::cout << std::endl;
}

void NQueens::DisplayMenu() const
{
    std::cout << "\n\tN-Queens Menu";
    std::cout << "\n\t=============";
    std::cout << "\n\t1. Play Game";
    std::cout << "\n\t2. Toggle Auto-solve: " << (m_AutoSolve ? "ON" : "OFF");
    std::cout << "\n\t3. Display Statistics";
    std::cout << "\n\t4. Display Current Board";
    std::cout << "\n\t0. Return to Main Menu";
    std::cout << std::endl;
}