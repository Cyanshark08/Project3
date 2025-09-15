#pragma once
#include "SubApp.h"

#include <iostream>
#include <vector>

class TicTacToe : public SubApp
{
public:

	/*
	* PreCondition: N/A
	* PostCondition: initialize private members and board to default values
	*/
	TicTacToe();

	/*
	* PreCondition: newSize must be a positive integer value
	* PostCondition: initialize the size to newSize and resize the board
	* 
	* @param The size of the board
	*/
	TicTacToe(size_t newSize);

	/*
	* PreCondition: N/A
	* PostCondition: Run the game for the player
	*/
	void Run() override;

	/*
	* PreCondition: N/A
	* PostCondition: Reset the board to its initial state (no squares taken)
	*/
	void Restart() override;

	/*
	* PreCondition: N/A
	* PostCondition: Reset the size, games, and board
	*/
	void Clean() override;

private:

	/*
	* PreCondition: I and J must be valid indices within the 2D vector
	* PostCondition: set the specified index of the vector to 1 (player mark)
	* 
	* @param The indexes of the area to mark
	*/
	void setPlayerMove(size_t i, size_t j);

	/*
	* PreCondition: N/A
	* PostCondition: set an index on the board to 2 (computer mark)
	*/
	void setComputerMove();

	/*
	* PreCondtion: newSize must be a positive integer value
	* PostCondition: set size to newSize
	* 
	* @param The size of the board
	*/
	void setSize(size_t newSize);

	/*
	* PreCondition: N/A
	* PostCondition: check if there is a winner on the board. Return the number corresponding to the winner
	* 
	* @return The number corresponding to the winner (0-none, 1-player, 2-computer)
	*/
	int checkWinner() const;

	/*
	* PreCondition: N/A
	* PostCondition: Return true if there are still empty spots on the board
	* 
	* @return A boolean statement regarding the state of the board
	*/
	bool isMovesLeft() const;

	/*
	* PreCondition: Depth, alpha, and beta must be a positive integer value, isMax must be a boolean statement
	* PostCondition: Return the score of the highest scoring move the computer can make
	* 
	* @param The amount of moves into the game (depth), whose turn is currently being played (isMax), the highest score 
	* by the computer (alpha), and the highest score by the human (beta)
	* @return The highest score corresponding to the best move
	*/
	int miniMax(int depth, bool isMax, int alpha, int beta);

	/*
	* PreCondition: N/A
	* PostCondition: Return the score of the current state of the board
	* 
	* @return The score used to determine the best move
	*/
	int evaluateBoard() const;

	/*
	* PreCondition: N/A
	* PostCondition: Display the board, substituting the 0, 1, 2, with an empty square, X, or O
	*/
	void displayBoard() const;

	/*
	* PreCondition N/A
	* PostCondition: Display the TicTacToe informational paragraph
	*/
	void displayInfo() const;

	void HandleInput(char p_Input) override;

private:
	size_t size;
	std::vector<std::vector<int32_t>> m_Board;
};

