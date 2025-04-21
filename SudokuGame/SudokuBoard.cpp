#include <iostream>
#include "SudokuBoard.hpp"
#include <fstream>
#include <stdexcept>
#include <cctype>

SudokuBoard:: SudokuBoard(): board(9, vector<int>(9, 0)) {
    
}


bool SudokuBoard::  validateConstrains(int row, int col, int value) {
    /* Check if anything is repeated in the same row*/
    for(int i = 0; i < 9; i++) {
        // row - 1 as the user will input rows from 1-9 not 0-8
        if (board[row - 1][i] == value)  {
            return false;
        }
    }

    /* Check if anything is repeated in the same col*/ 
    for(int i = 0; i < 9; i++) {
        if(board[i][col - 1] == value) {
            return false;
        }
    }

    int boxStartRow = (row - 1) / 3 * 3;  // Get top-left row of the 3x3 box
    int boxStartCol = (col - 1) / 3 * 3;  // Get top-left column of the 3x3 box

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[boxStartRow + i][boxStartCol + j] == value) {
                return false;
            }
        }
    }
    return true;
}


void SudokuBoard:: setElement(int row, int col, int value) {
    if (row > 9 || row < 1) {
        throw out_of_range("Row must be between 1 and 9");
    }
    else if (col > 9 || col < 1) {
        throw out_of_range("Column must be between 1 and 9");
    }

    else if (board[row - 1][col - 1] != 0 ) {
        throw out_of_range("This place is not empty");
    }

    else if( validateConstrains(row, col, value) == true) {
            board[row - 1][col - 1] = value;
            cout  << "Move is accepted" << endl;
    }
    else {
        cout << "Wrong number" << endl;
    }

}

void SudokuBoard:: loadBoardFromFile() {
    ifstream inputFile("puzzle.txt");
    if(!inputFile.is_open()) {
        throw runtime_error("You tried to load a sudoku board from a file that doesn't exist");
    }
    string line;
    vector <int> allNumbers;
    while(getline(inputFile, line))  {
        for(int j = 0; j < line.length(); j++) {
            if(isdigit(line[j])) {
                allNumbers.push_back(line[j] - '0');
            }
            else if (line[j] == '.') {
                allNumbers.push_back(0);
            }
        }
    }
    inputFile.close();

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            board[i][j] = allNumbers[i * 9 + j];
        }
    }
    
}

void SudokuBoard:: PrintBoard() {
    cout << "*************************" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                cout << ".";
            } else {
                cout << board[i][j];
            }

            
            if (j < 8) {
                cout << " ";
            }

            
            if ((j + 1) % 3 == 0 && j != 8) {
                cout << "| ";
            }
        }
        cout << endl;

        
        if ((i + 1) % 3 == 0 && i != 8) {
            cout << "*************************" << endl;
        }
    }
    cout << endl << endl;
}

void SudokuBoard:: PrintToFile() {
    ofstream outputFile("UserProgress.txt");
        if(!outputFile.is_open()) {
            throw runtime_error("File is not Open to write the board into it in user mode");
        }
    else {

        outputFile << "*************************" << endl;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    outputFile << ".";
                } else {
                    outputFile << board[i][j];
                }

                
                if (j < 8) {
                    outputFile << " ";
                }

                
                if ((j + 1) % 3 == 0 && j != 8) {
                    outputFile << "| ";
                }
            }
            outputFile << endl;

            
            if ((i + 1) % 3 == 0 && i != 8) {
                outputFile << "*************************" << endl;
            }
        }   
    }
}

bool SudokuBoard::isComplete() const {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0)
                return false;
        }
    }
    return true;
}
