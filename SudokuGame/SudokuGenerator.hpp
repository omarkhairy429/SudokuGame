#ifndef SUDOKU_GENERATOR_HPP
#define SUDOKU_GENERATOR_HPP

#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"

class SudokuGenerator {
    private:    
        SudokuSolver solver;
        bool solveBoard(SudokuBoard & gboard);
        void PrintBoard(SudokuBoard & gboard);
        void removeAfterSolve(SudokuBoard & gboard, int numberOfRemoves);
        void randomFill(SudokuBoard & gboard);
        bool hasUniqueSolution(SudokuBoard & gboard);
    public:
        SudokuGenerator();
        void generate(SudokuBoard & gboard, int difficulty);
        
};

#endif 
