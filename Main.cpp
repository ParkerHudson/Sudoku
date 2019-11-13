/*
By Gregory Hudson
Fall semester 2019 - COP 3530
Program that implements the requirements of homework 
*/

#include "Sudoku.h"
#include <iostream>

bool checkSame(const int array1[], const int array2[], int start, int end);
int main(void)
{
	// Put your name in the statement below
	std::cout << "Homework 5 test case results by Gregory Hudson" << std::endl;

	int array[81] = { 2, 0, 0, 0, 0, 4, 8, 0, 0, 5, 0, 9, 0, 0, 3, 0, 6, 0, 0, 3, 0, 9, 0, 1, 0, 0, 5, 0, 0, 1, 0, 0, 0, 9, 0, 2, 3, 9, 0, 0, 0, 0, 0, 1, 7, 7, 0, 5, 0, 0, 0, 4, 0, 0, 1, 0, 0, 6, 0, 9, 0, 7, 0, 0, 4, 0, 2, 0, 0, 6, 0, 1, 0, 0, 8, 5, 0, 0, 0, 0, 9 };
	int testArray[81];
	// test cases for
	int testCount = 1;  // used to track test numbers
	int errorCode;
	Sudoku a;
	a.display();

	a.getBoard(testArray);
	if (checkSame(testArray, array, 0, 80) == true)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.addNumber(0, 5, 3);
	if (errorCode == Sudoku::OUT_OF_BOUNDS_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.addNumber(10, 5, 3);
	if (errorCode == Sudoku::OUT_OF_BOUNDS_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.addNumber(5, 0, 3);
	if (errorCode == Sudoku::OUT_OF_BOUNDS_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.addNumber(5, 10, 3);
	if (errorCode == Sudoku::OUT_OF_BOUNDS_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.addNumber(5, 5, 0);
	if (errorCode == Sudoku::OUT_OF_BOUNDS_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.addNumber(5, 5, 10);
	if (errorCode == Sudoku::OUT_OF_BOUNDS_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	a.getBoard(testArray);
	if (checkSame(testArray, array, 0, 80) == true)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.addNumber(1, 1, 1);
	if (errorCode == Sudoku::OUT_OF_BOUNDS_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	a.getBoard(testArray);
	if (checkSame(testArray, array, 0, 80) == true)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.addNumber(7, 7, 7);
	if (errorCode == Sudoku::GAME_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	array[60] = 7;
	a.getBoard(testArray);
	if (checkSame(testArray, array, 0, 80) == true)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.addNumber(7, 7, 1);
	if (errorCode == Sudoku::GAME_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	array[60] = 1;
	a.getBoard(testArray);
	if (checkSame(testArray, array, 0, 80) == true)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.addNumber(7, 7, 9);
	if (errorCode == Sudoku::GAME_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	array[60] = 9;
	a.getBoard(testArray);
	if (checkSame(testArray, array, 0, 80) == true)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.remove(7, 7);
	if (errorCode == Sudoku::NO_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	array[60] = Sudoku::NO_ENTRY;
	a.getBoard(testArray);
	if (checkSame(testArray, array, 0, 80) == true)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	errorCode = a.remove(1, 1);
	if (errorCode == Sudoku::OUT_OF_BOUNDS_ERROR)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	a.getBoard(testArray);
	if (checkSame(testArray, array, 0, 80) == true)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	a.addNumber(1, 2, 1);
	if (a.hasPlayerWonGame() == false)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	a.addNumber(1, 2, 1);
	a.addNumber(1, 3, 6);
	a.addNumber(1, 4, 7);
	a.addNumber(1, 5, 5);
	a.addNumber(1, 8, 9);
	a.addNumber(1, 9, 3);
	a.addNumber(2, 2, 7);
	a.addNumber(2, 4, 8);
	a.addNumber(2, 5, 2);
	a.addNumber(2, 7, 1);
	a.addNumber(2, 9, 4);
	a.addNumber(3, 1, 8);
	a.addNumber(3, 3, 4);
	a.addNumber(3, 5, 6);
	a.addNumber(3, 7, 7);
	a.addNumber(3, 8, 2);
	a.addNumber(4, 1, 4);
	a.addNumber(4, 2, 6);
	a.addNumber(4, 4, 3);
	a.addNumber(4, 5, 7);
	a.addNumber(4, 6, 5);
	a.addNumber(4, 8, 8);
	a.addNumber(5, 3, 2);
	a.addNumber(5, 4, 4);
	a.addNumber(5, 5, 8);
	a.addNumber(5, 6, 6);
	a.addNumber(5, 7, 5);
	a.addNumber(6, 2, 8);
	a.addNumber(6, 4, 1);
	a.addNumber(6, 5, 9);
	a.addNumber(6, 6, 2);
	a.addNumber(6, 8, 3);
	a.addNumber(6, 9, 6);
	a.addNumber(7, 2, 5);
	a.addNumber(7, 3, 3);
	a.addNumber(7, 5, 4);
	a.addNumber(7, 7, 2);
	a.addNumber(7, 9, 8);
	a.addNumber(8, 1, 9);
	a.addNumber(8, 3, 7);
	a.addNumber(8, 5, 3);
	a.addNumber(8, 6, 8);
	a.addNumber(8, 8, 5);
	a.addNumber(9, 1, 6);
	a.addNumber(9, 2, 2);
	a.addNumber(9, 5, 1);
	a.addNumber(9, 6, 7);
	a.addNumber(9, 7, 3);
	a.addNumber(9, 8, 4);
	if (a.hasPlayerWonGame() == true)
		std::cout << "Test Case " << testCount << " Passed" << std::endl;
	else
		std::cout << "Test Case " << testCount << " Failed" << std::endl;
	testCount++;

	return 0;
}

bool checkSame(const int array1[], const int array2[], int start, int end)
{
	bool rv = true;
	for (int i = start; i <= end; i++)
	{
		if (array1[i] != array2[i])
		{
			rv = false;
		}
	}
	return rv;
}





