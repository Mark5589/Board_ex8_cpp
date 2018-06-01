//
// Created by mark  gurin on 07/05/2018.
//

#include "Cell.hpp"

void Cell::setCell(const char &c) {
    if(c == 'X' || c == 'O' || c == '.'){
        this->val = c;
    }
    this->val = c;

}

Cell &Cell::operator=(char c) {
    if(c == 'X' || c == 'O' || c == '.'){
        this->val = c;
        return (*this);
    }
    else{
        IllegalCharException ex;
        ex.setChar(c);
        throw ex;
    }

}

char Cell::getCell() const {
    return this->val;
}

Cell::operator char() const {
    return this->getCell();
}

std::ostream &operator<<(std::ostream& os, Cell &cell) {
    os << cell.getCell();
    return os;
}
