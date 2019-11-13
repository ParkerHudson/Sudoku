/*
By Gregory Hudson
Fall 2019 - COP 3530

*/
#include "Sudoku.h"
#include <vector>
#include <iostream>
#include <string>
// The games array holds the numbers for each game. There are 81 numbers for each game. There is only one
// game defined for this definition (more can be easily added). The first 9 numbers in the array (elements 0 to 8) represent 
// the first row of a game. The 2nd 9 numbers in the array (elements 9 to 17) represent the 2nd row of a game.
// The show array represents the initial game conditions. If a number is 0 (NO_ENTRY) then it is missing
// on the game board. The numbers from 1 to 9 in the show array are initially provided to the user on the game board.
// These initial numbers are "fixed" on the game board and cannot be changed by the member functions (by the player of the game).
const int Sudoku::games[][Sudoku::TOTAL_BOXES] = { { 2,1,6,7,5,4,8,9,3,  5,7,9,8,2,3,1,6,4,  8,3,4,9,6,1,7,2,5,  4,6,1,3,7,5,9,8,2,  3,9,2,4,8,6,5,1,7,  7,8,5,1,9,2,4,3,6,  1,5,3,6,4,9,2,7,8,  9,4,7,2,3,8,6,5,1,  6,2,8,5,1,7,3,4,9 } };
const int Sudoku::show[][Sudoku::TOTAL_BOXES] = {  { 2,0,0,0,0,4,8,0,0,  5,0,9,0,0,3,0,6,0,  0,3,0,9,0,1,0,0,5,  0,0,1,0,0,0,9,0,2,  3,9,0,0,0,0,0,1,7,  7,0,5,0,0,0,4,0,0,  1,0,0,6,0,9,0,7,0,  0,4,0,2,0,0,6,0,1,  0,0,8,5,0,0,0,0,9 } };

// The default constructor will select a game to play. There is only 1 game defined for this
// definition. The default constructor will initialize the game board using the show array.
// The game board must be implemented using an array of vectors where each vector represents
// one row of the game board.
Sudoku::Sudoku()
{
	gameNum = 0;  // would be random if more than 1 game
	for (int i = 0; i < MAX_ROW_NUM; i++)
	{ // traverse the rows
		for (int j = 0; j < MAX_COLUMN_NUM; j++)
		{ // traverse the columns and transfer the numbers
			board[i].push_back(show[gameNum][(i*MAX_COLUMN_NUM)+j]);
		}
	}
}
// The member function addNumber() will attempt to add a number to the game board.
// The row input variable represents the row of the input. Valid row inputs are from MIN_ROW_NUM to MAX_ROW_NUM inclusive.
// The column input variable represents the column of the input. Valid column inputs are from MIN_COLUMN_NUM to MAX_COLUMN_NUM
// inclusive. The number input variable represents the number to be placed at the row and column. 
// Valid number inputs are from MIN_NUM to MAX_NUM inclusive. The return value is the status of the function.
// An OUT_OF_BOUNDS_ERROR is returned if the row, column, or number is invalid. An OUT_OF_BOUNDS_ERROR is also returned if the
// the valid row/column is a fixed number (initially shown to the user at the game start).
// In the case of an OUT_OF_BOUNDS_ERROR error, the number is not inserted to the game board.
// If there is no OUT_OF_BOUNDS_ERROR, then check for a GAME_ERROR. 
// A GAME_ERROR is returned if a valid number to be placed at a valid row/column position breaks the sudoku game play rules.
// In the case of a GAME_ERROR, the number is inserted to the game board.
// For example, for game 1 (the only gamefor this definition), addNumber(1, 2, 9) would return a GAME_ERROR
// and insert a 9 to row/column position 1/2 on the game board.
// If an OUT_OF_BOUNDS_ERROR and GAME_ERROR are not detected, then return a NO_ERROR.
// In the case of NO_ERROR, the number is placed on the game board.
int Sudoku::addNumber(int row, int column, int number)
{
	int rv = checkBounds(row, column, number); // check for errors
	if (rv == NO_ERROR)
	{ // if no error then check for game errors
		for (int i = 0; i < MAX_ROW_NUM; i++)
		{ // traverse an individual column
			if (board[i][column - 1] == number)
			{ // check if a duplicate number is in a specific column
				rv = GAME_ERROR;
			}
		}
		for (int i = 0; i < MAX_COLUMN_NUM; i++)
		{ // traverse an individual row
			if (board[row - 1][i] == number)
			{ // check if a duplicate number is in a specific row
				rv = GAME_ERROR;
			}
		}
		int startRow = (row - 1); 
		int startColumn = (column - 1);
		startRow = startRow - (startRow % BOX_SIZE);
		startColumn = startColumn - (startColumn % BOX_SIZE);
		for (int i = startRow; i < startRow + BOX_SIZE; i++)
		{ // traverse the rows for the box
			for (int j = startColumn; j < startColumn + BOX_SIZE; j++)
			{ // traverse the columns for the box
				if (board[i][j] == number)
				{ // check if a duplicate number is in a box
					rv = GAME_ERROR;
				}
			}
		}
		board[row - 1][column - 1] = number;
	}
	return rv;
}
// The member function remove() will attempt to remove a number to the game board.
// The row input variable represents the row of the input. Valid row inputs are from MIN_ROW_NUM to MAX_ROW_NUM inclusive.
// The column input variable represents the column of the input. Valid column inputs are from MIN_COLUMN_NUM to MAX_COLUMN_NUM
// inclusive. The return value is the status of the function.
// An OUT_OF_BOUNDS_ERROR is returned if the row or column is invalid. An OUT_OF_BOUNDS_ERROR is also returned if the
// the valid row/column is a fixed number (initially shown to the user at the game start). If there are no errors encountered, then
// the number at the corresponding row/column will be removed.
int Sudoku::remove(int row, int column)
{
	int rv = checkBounds(row, column, MIN_NUM); // check for errors
	if (rv == NO_ERROR)
	{ // if no errors then remove the number
		board[row - 1][column - 1] = NO_ENTRY;
	}
	return rv;
}
int Sudoku::checkBounds(int row, int column, int number)
{
	int rv = NO_ERROR;
	if (row < MIN_ROW_NUM || row > MAX_ROW_NUM || column < MIN_COLUMN_NUM || column > MAX_COLUMN_NUM || number < MIN_NUM || number > MAX_NUM)
	{ // check the row, column, and number boundaries
		rv = OUT_OF_BOUNDS_ERROR;
	}
	else
	{ // if inputs are valid then check if the row/column entry is fixed
		int i = ((row - 1) * MAX_COLUMN_NUM) + (column - 1);
		if (show[gameNum][i] != NO_ENTRY)
		{ // if a fixed number then
			rv = OUT_OF_BOUNDS_ERROR;
		}
	}
	return rv;
}
void Sudoku::playGame()
{
	int rv;
	std::string st;
	bool win = false;
	while (win == false)
	{
		rv = OUT_OF_BOUNDS_ERROR;
		std::cout << "Enter next command>";
		std::getline(std::cin, st);
		if (st.length() >= 1)
		{
			if (st[0] == 'i')
			{
				if (st.length() == 7)
				{
					if ((st[1] == ' ') && (st[3] == ' ') && (st[5] == ' ') && (st[2] >= '1') && (st[2] <= '9') && (st[4] >= '1') && (st[4] <= '9') && (st[6] >= '1') && (st[6] <= '9'))
					{
						rv = addNumber(st[2] - 48, st[4] - 48, st[6] - 48);
						win = hasPlayerWonGame();
					}
				}
			}
			else if (st[0] == 'r')
			{
				if (st.length() == 5)
				{
					if ((st[1] == ' ') && (st[3] == ' ') && (st[2] >= '1') && (st[2] <= '9') && (st[4] >= '1') && (st[4] <= '9'))
					{
						rv = remove(st[2] - 48, st[4] - 48);
					}
				}
			}
			else if (st[0] == 'q')
			{
				break;
			}
		}
		if (rv == OUT_OF_BOUNDS_ERROR)
		{
			std::cout << "Invalid command" << std::endl;
		}
		else 
		{
			display();
		}
	}
	if (win == true)
	{
		std::cout << "Congratulations, you won the game" << std::endl;
	}
}
// The member function hasPlayerWonGame() will determine if the player has correctly solved the puzzle.
// The return value of true is returned if the player has correctly solved the puzzle, otherwise false is returned.
// To win the game, all entries in the game board must be entered and match the solution provided in the games array.
bool Sudoku::hasPlayerWonGame()
{
	bool rv = true; // default to a win
	for (int i = 0; i < MAX_ROW_NUM; i++)
	{ // traverse the rows
		for (int j = 0; j < MAX_COLUMN_NUM; j++)
		{ // traverse the column
			if (board[i][j] != games[gameNum][(i*MAX_COLUMN_NUM) + j])
			{ // if any mismatch then set to false and terminate the loop
				rv = false;
				break;
			}
		}
	}
	return (rv);
}
// The member function display() will display the current state of the game board.
// See an image example provided for the homework.
void Sudoku::display()
{
	for (int i = 0; i < MAX_ROW_NUM; i++)
	{ // traverse the rows
		if (i % 3 == 0)
		{
			std::cout << " -----------------------------" << std::endl;
		}
		for (int j = 0; j < MAX_COLUMN_NUM; j++)
		{ // traverse the columns
			if (j % 3 == 0)
				std::cout << "| " << (board[i][j] == NO_ENTRY ? " " : std::to_string(board[i][j])) << " ";
			else
				std::cout << " " << (board[i][j] == NO_ENTRY ? " " : std::to_string(board[i][j])) << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << " -----------------------------" << std::endl << std::endl;
}
// The member function getBoard() will populate the array input variable with the current game board values.
// The first row of the game board is entered to the first 9 elements of array (elements 0 to 8).
// The second row of the game board is entered to the next 9 elements of array (elements 9 to 17).
// For enteries that do not exist (not entered yet), they should be represented by NO_ENTRY.
// For example, for the game provided, at the beginning of the game before any new numbers are entered,
// the first 9 elements of array should be 2,0,0,0,0,4,8,0,0.
void Sudoku::getBoard(int array[])
{
	int k = 0;
	for (int i = 0; i < MAX_ROW_NUM; i++)
	{ // traverse the rows
		for (int j = 0; j < MAX_COLUMN_NUM; j++)
		{ // traverse the columns
			array[k] = board[i][j];
			k++;
		}
	}
}
