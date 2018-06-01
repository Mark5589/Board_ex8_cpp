//
// Created by mark  gurin on 07/05/2018.
//
#pragma once

#ifndef BOARD_MYEXCEPTION_HPP
#define BOARD_MYEXCEPTION_HPP

#include <iostream>
#include <exception>


class IllegalCoordinateException: public std::exception{
    int x, y;
public:
    void set(int m1,int n1){this->x =m1; this->y=n1;}
    std::string theCoordinate() const {return std::to_string(x) +","+ std::to_string(y);}
};

class IllegalCharException: public std::exception{
    char c;
public:
    char theChar()const {return c;}
    void setChar(char c1){c = c1;}
};


#endif //BOARD_MYEXCEPTION_HPP
