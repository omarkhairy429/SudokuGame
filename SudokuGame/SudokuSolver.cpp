#include "SudokuSolver.hpp"
#include "SudokuBoard.hpp"

bool SudokuSolver::solve(SudokuBoard &sboard) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (sboard.board[row][col] == 0) {  // Find empty cell
                for (int num = 1; num <= 9; num++) {  // Try numbers 1 to 9
                    if (sboard.validateConstrains(row + 1, col + 1, num)) {
                        sboard.board[row][col] = num;  // Place the number
                        if (solve(sboard)) {  // Recursively try to solve the board
                            return true;
                        }
                        sboard.board[row][col] = 0;  // Undo move if it doesn't work
                    }
                }
                return false;
            }
        }
    }
    return true;  // All cells are filled
}
