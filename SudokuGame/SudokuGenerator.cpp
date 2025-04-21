#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SudokuGenerator.hpp"

SudokuGenerator::SudokuGenerator() {
    srand(time(0));  
}

bool SudokuGenerator::solveBoard(SudokuBoard & gboard) {
    return solver.solve(gboard);  // Uses the existing solver to solve the board
}

void SudokuGenerator::PrintBoard(SudokuBoard & gboard) {
    gboard.PrintBoard();
}

void SudokuGenerator::removeAfterSolve(SudokuBoard & gboard, int numberOfRemoves) {
    int count = 0;
    while (count < numberOfRemoves) {
        int row = rand() % 9;
        int col = rand() % 9;

        if (gboard.board[row][col] != 0) {
            int temp = gboard.board[row][col];
            gboard.board[row][col] = 0;

            if (!hasUniqueSolution(gboard)) {
                gboard.board[row][col] = temp;
            } else {
                count++;
            }
        }
    }
}


bool SudokuGenerator::hasUniqueSolution(SudokuBoard & gboard) {
    SudokuBoard tempBoard = gboard;  
    int solutionCount = 0;

    
    if (solveBoard(tempBoard)) {
        solutionCount++;
    }

    
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (tempBoard.board[row][col] == 0) {  
                for (int num = 1; num <= 9; num++) {
                    if (tempBoard.validateConstrains(row + 1, col + 1, num)) {
                        tempBoard.board[row][col] = num;
                        if (solveBoard(tempBoard)) {
                            solutionCount++;
                        }
                        tempBoard.board[row][col] = 0;  
                    }
                }
            }
        }
    }

    return solutionCount == 1; 
}

void SudokuGenerator::randomFill(SudokuBoard & gboard) {
    int numberOfFills = 10;
    int count = 0;

    while (count < numberOfFills) {
        int random_number = rand() % 9 + 1; 
        int random_row = rand() % 9; 
        int random_col = rand() % 9;

        // Check if the value can be placed at this position
        if (gboard.validateConstrains(random_row + 1, random_col + 1, random_number)) {
            gboard.board[random_row][random_col] = random_number; // Set value in the board
            count++;
        }
    }
}


void SudokuGenerator::generate(SudokuBoard & gboard, int difficulty) {
    randomFill(gboard);
    if (solveBoard(gboard)) {
        removeAfterSolve(gboard, difficulty);
    } else {
        randomFill(gboard);
        removeAfterSolve(gboard, difficulty);
    }
}

