#pragma once
#include "SubApp.h"
#include <vector>
#include <string>

class NQueens : public SubApp
{
public:
    NQueens();

    void Run() override;
    void Restart() override;
    void Clean() override;

private:
    void HandleInput(char p_Input) override;

    void DisplayBoard() const;
    void DisplayInfo() const;
    bool IsSafe(int row, int col) const;
    bool Solve(int col);
    bool SolveAllSolutions(int col);
    void CountSolutions();
    void ResetBoard();

    void DisplayStatistics() const;
    void DisplayMenu() const;

private:
    int m_BoardSize;
    std::vector<std::vector<bool>> m_Board;
    int m_SolutionCount;
    int m_TotalGames;
    int m_FastestSolution;
    int m_SlowestSolution;
    float m_AverageTime;
    bool m_AutoSolve;
};