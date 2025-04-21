#include "SudokuGame.hpp"
#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include "SudokuGenerator.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>

using namespace std;

SudokuGame::SudokuGame() {
    int difficultyChoice;
    cout << "Select difficulty level:\n";
    cout << "1) Easy (20 cells removed)\n";
    cout << "2) Medium (30 cells removed)\n";
    cout << "3) Hard (40 cells removed)\n";
    cout << "Choice: ";
    difficultyChoice = getValidatedInt(1, 3);

    int numberToRemove;
    switch (difficultyChoice) {
        case 1: numberToRemove = 20; break;
        case 2: numberToRemove = 30; break;
        case 3: numberToRemove = 40; break;
    }

    SudokuGenerator generator;
    generator.generate(sboard, numberToRemove);
}

int SudokuGame::getValidatedInt(int min, int max) {
    int input;
    while (true) {
        try {
            cin >> input;

            // Check if input is an integer
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
                throw invalid_argument("Invalid input. Please enter an integer.");
            }

            // Check range
            if (input < min || input > max) {
                throw out_of_range("Choice out of range.");
            }

            return input;
        } catch (const exception& e) {
            cout << e.what() << " Try again: ";
        }
    }
}

void SudokuGame::startGame() {
    while (true) {
        if (sboard.isComplete()) {
            cout << "\n Congratulations!!!! You've completed the Sudoku successfully! \n";
            cout << "Do you want to play again?\n";
            cout << "1) Yes\n";
            cout << "2) No (Exit)\n";
            cout << "Choice: ";
            int replayChoice;
            replayChoice = getValidatedInt(1, 2);

            if (replayChoice == 1) {
                *this = SudokuGame(); // restart with new puzzle
                continue;
            } else {
                cout << "Thanks for playing! Goodbye!" << endl;
                break;
            }
        }

        sboard.PrintBoard();
        cout << "\n1) Enter a move\n";
        cout << "2) Solve automatically\n";
        cout << "3) Load puzzle from file\n";
        cout << "4) Save current puzzle to file\n";
        cout << "5) Exit\n";
        cout << "Choice: ";
        choice = getValidatedInt(1, 5);

        switch (choice) {
            case 1: option1(); break;
            case 2: option2(); break;
            case 3: option3(); break;
            case 4: option4(); break;
            case 5:
                cout << "Exiting the game." << endl;
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

void SudokuGame::option1() {
    SudokuBoard tempBoard = sboard;
    SudokuSolver solveTemp;

    if (!solveTemp.solve(tempBoard)) {
        cout << "Current board cannot be solved. Please reset or load a valid puzzle." << endl;
        return;
    }

    int row, col, value;
    cout << "Enter row (1-9): ";
    row = getValidatedInt(1, 9);
    cout << "Enter column (1-9): ";
    col = getValidatedInt(1, 9);
    cout << "Enter value (1-9): ";
    value = getValidatedInt(1, 9);

    if (tempBoard.board[row - 1][col - 1] != value) {
        cout << "Wrong Move." << endl;
        return;
    }

    try {
        sboard.setElement(row, col, value);
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }

    try {
        sboard.PrintToFile();
    } catch (runtime_error& e) {
        cout << e.what() << endl;
    }
}

void SudokuGame::option2() {
    SudokuSolver solveBoard;
    if (solveBoard.solve(sboard)) {
        sboard.PrintBoard();
    } else {
        cout << "This Board has no solution." << endl;
    }
}

void SudokuGame::option3() {
    try {
        sboard.loadBoardFromFile();
        cout << "The board is loaded successfully." << endl;
    } catch (runtime_error& e) {
        cout << e.what() << endl;
    }
}

void SudokuGame::option4() {
    try {
        sboard.PrintToFile();
        cout << "File is saved successfully." << endl;
    } catch (runtime_error& e) {
        cout << e.what() << endl;
    }
}

void SudokuGame::option5() {
    cout << "Exiting the game." << endl;
}
