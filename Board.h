//
// Created by mark  gurin on 04/05/2018.
//
#pragma once

#ifndef BOARD_BOARD_HPP
#define BOARD_BOARD_HPP

#include <iostream>
#include <initializer_list>
#include <string>
#include "Cell.hpp"
#include "MyException.hpp"
#include <fstream>
#include <cmath>
#include <ctime>
#include <sys/time.h>


struct Coordinate{
    uint x;
    uint y;
};

struct RGB {
    uint8_t red, green, blue;
public:
    RGB() {}
    RGB(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {}
};

class Board {
    int x,y;
    int size_;
    Cell **board;

public:
	Board(){}
    Board(int n);
    ~Board();
    int size()const {return size_;}
    friend std::ostream&operator<<(std::ostream& stream , const Board& board);
    friend std::istream&operator>>(std::istream& stream ,  Board& board);

      Cell& operator[](std::initializer_list<uint> list);
      Cell& operator[](const Coordinate& c) const;
//      Board& operator[](std::initializer_list<int> list);
    void setX(int x){this->x = x;}
    void setY(int y){this->y = y;}
    Board&operator=(char c);
    Board&operator=(const Board&other);

    const std::string draw(int n);



};






#endif //BOARD_BOARD_HPP
