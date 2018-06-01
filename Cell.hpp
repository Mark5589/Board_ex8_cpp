//
// Created by mark  gurin on 07/05/2018.
//

#pragma once

#ifndef BOARD_CELL_HPP
#define BOARD_CELL_HPP

//#include "Board.hpp"
#include <iostream>
#include "MyException.hpp"
class Cell {
    char val;

public:
    Cell(){}
    void setCell(const char &c );
    char getCell()const;
    Cell&operator=(char c);
    operator char() const;
    friend std::ostream&operator<<(std::ostream& os, Cell &cell);
};


#endif //BOARD_CELL_HPP
