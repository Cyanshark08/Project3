#pragma once
#include "SubApp.h"
#include <vector>
#include <string>

class NQueens : public SubApp
{
public:
    NQueens();

    /*
    * PreCondition: N/A
    * PostCondition: Run the n-Queens game for the player
    */
    void Run() override;

    /*
    * PreCondition: N/A
    * PostCondition: Reset the board to its initial state
    */
    void Restart() override;

    /*
    * PreCondition: N/A
    * PostCondition: Clean up the board and reset all variables
    */
    void Clean() override;

private:
    /*
    * PreCondition: Valid board size
    * PostCondition: Initialize the board with the specified size
    */
    void InitializeBoard(size_t boardSize);

    /*
    * PreCondition: Valid row and column indices
    * PostCondition: Place or remove a queen at the specified position
    */
    void ToggleQueen(size_t row, size_t col);

    /*
    * PreCondition: Valid board state
    * PostCondition: Check if the current board configuration is valid (no queens attacking each other)
    */
    bool IsValidConfiguration() const;

    /*
    * PreCondition: Valid row and column indices
    * PostCondition: Check if placing a queen at (row, col) would conflict with existing queens
    */
    bool IsSafe(size_t row, size_t col) const;

    /*
    * PreCondition: Valid board state
    * PostCondition: Display the current board state
    */
    void DisplayBoard() const;

    /*
    * PreCondition: N/A
    * PostCondition: Display information about the n-Queens problem
    */
    void DisplayInfo() const;

    /*
    * PreCondition: Valid input character
    * PostCondition: Handle user input for the n-Queens game
    */
    void HandleInput(char p_Input) override;

    /*
    * PreCondition: Valid board state
    * PostCondition: Check if the puzzle is solved (all queens placed with no conflicts)
    */
    bool IsSolved() const;

private:
    std::vector<std::vector<bool>> m_Board;
    size_t m_BoardSize;
    size_t m_QueensPlaced;
    size_t m_Moves;
};