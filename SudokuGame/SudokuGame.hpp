#ifndef SUDOKUGAME_HPP
#define SUDOKUGAME_HPP

#include "SudokuBoard.hpp"

class SudokuGame {
private:
    SudokuBoard sboard;
    int choice;

public:
    SudokuGame();  
    void startGame();  
    void option1();  
    void option2();  
    void option3();  
    void option4();  
    void option5();  
    
    int getValidatedInt(int min, int max);  
};

#endif
