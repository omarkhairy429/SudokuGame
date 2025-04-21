#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include <iostream>
#include <vector>

using namespace std;

class SudokuBoard {
    private:
        vector<vector<int>> board;
    public:
        /* Constructor making
           The board ready to play
           with specific game values*/
        SudokuBoard();

        void PrintToFile();

        void loadBoardFromFile();

        void PrintBoard();

        bool validateConstrains(int row, int col, int value);

        void setElement(int row, int col, int value);

        bool isComplete() const;
        
        friend class SudokuSolver;
        friend class SudokuGenerator;
        friend class SudokuGame;
};

#endif 