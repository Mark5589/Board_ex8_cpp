//
// Created by mark  gurin on 04/05/2018.
//

#include "Board.h"


Board::Board(int n) {
    this->size_ = n;
//    board = new char*[size()];
    board = new Cell*[size()];
    int i,j;
    for ( i = 0; i < size(); ++i) {
        this->board[i] = new Cell[size()];
    }
    for (i = 0; i < size(); ++i) {
        for (j = 0; j <size() ; j++) {
            this->board[i][j].setCell('.');
        }
    }
}

Board::~Board() {
    for (int i = 0; i < size(); ++i) {
        delete[] board[i];
    }
    delete[] board;

}

std::ostream &operator<<(std::ostream &stream, const Board &other) {
    for (int i = 0; i < other.size(); ++i) {
        for (int j = 0; j < other.size(); ++j) {
            stream << other.board[i][j].getCell();
        }
        stream<<"\n";
    }
    return stream;
}

std::istream &operator>>(std::istream &stream,  Board &board) {
    std::string line;
    stream >> line ;
    int len  = line.length();
    Board tmp(len);
    board = tmp;
    for(uint i = 0 ; i < line.length() ; ++i){
        Coordinate c{0, i};
        board[c] = line[i];
    }
    uint counter = 1 ;

    while(stream >> line){
            for(uint i = 0 ; i < line.length() ; ++i){
                Coordinate c{counter, i};
                board[c] = line[i];
            }
            ++counter;

    }

    return stream;

}


Cell& Board::operator[](std::initializer_list<uint> list) {
    int row = *list.begin();
    int col = *(list.begin()+1);
    setX(row);
    setY(col);
    if(row >= (*this).size() || row < 0 || col >= (*this).size() || col < 0){
        IllegalCoordinateException ex;
        ex.set(row, col);
        throw ex;
    }


    return this->board[row][col];
}

Cell &Board::operator[](const Coordinate& c) const{
    int row = c.x;
    int col = c.y;
//    setX(row);
//    setY(col);
    if(row >= (*this).size() || row < 0 || col >= (*this).size() || col < 0){
        IllegalCoordinateException ex;
        ex.set(row, col);
        throw ex;
    }


    return this->board[row][col];
}



Board &Board::operator=(char c) {
    if(c == 'X' || c == 'O'){
        int i,j;
        for (i = 0; i < size(); ++i) {
            for (j = 0; j <size() ; j++) {
                board[i][j] = c;
            }
        }
        return *this;
    }
    else if( c == '.'){
        int i, j;
        for (i = 0; i < size(); ++i) {
            for (j = 0; j <size() ; j++) {
                board[i][j] = '.';
            }
        }
        return *this;
    }


    else{
        IllegalCharException ex;
        ex.setChar(c);
        throw ex;
    }
}

Board &Board::operator=(const Board &other) {
    if((*this).board == other.board)return (*this);

        if((*this).size() != other.size()){
            for (int i = 0; i <this->size() ; ++i) {
                delete[] this->board[i];
            }
            delete[] this->board;

            this->size_= other.size();
            this->board = new Cell*[this->size()];
            for (int j = 0; j < size() ; ++j) {
                this->board[j] = new Cell[size()];
            }

            for (int k = 0; k < (*this).size(); ++k) {
                for (int i = 0; i < (*this).size(); ++i) {
                    this->board[k][i] =other.board[k][i];
                }
            }
        }
    return (*this);


}
const std::string Board::draw(int n) {
    //Credit To Bar-Zamsky & Shahar
//    time_t name;
//    struct tm* timeinfo;
//    char buffer[80];
//    time(&name);
//    timeinfo = localtime(&name);
//    strftime(buffer,sizeof(buffer),"%d-%m-%Y-%I:%M:%S",timeinfo);

    char buffer[80];
    int millisec;
    struct tm* tm_info;
    struct timeval tv;

    gettimeofday(&tv, NULL);

    millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
    if (millisec>=1000) { // Allow for rounding up to nearest second
        millisec -=1000;
        tv.tv_sec++;
    }

    tm_info = localtime(&tv.tv_sec);

    strftime(buffer, 80, "%d-%m-%Y-%I:%M:%S", tm_info);

    std::string str(buffer);
    std::string str_mil = std::to_string(millisec);
    std::string fileName= "pic:"+str+str_mil+".ppm";
    // - end -

    const int dimx = n, dimy = n;
    std::ofstream imageFile(fileName, std::ios::out | std::ios::binary);
    imageFile << "P6" << std::endl << dimx <<" " << dimy << std::endl << 255 << std::endl;
    RGB image[dimx][dimy];

    //Make The background
    for(int i =0 ; i < dimx ; ++i){
        for(int j = i ; j < dimy ; ++j){
            image[i][j]={255,229,204};
        }
    }
    for(int j =0 ; j < dimx ; ++j){
        for(int i = j ; i < dimy ; ++i){
            image[i][j]={255,255,204};
        }
    }
    // Make the Grid
    int cell_size = n/size();
    for(int i = cell_size ; i < n ; i+=cell_size){
        for(int j =0 ; j < n ; ++j){
            image[i][j] = {0,0,0};
            image[j][i] = {0,0,0};
        }
    }

    //Insert 'X' 'O' '.'
    for (int i = 0; i < size() ; ++i) {
        for (int j = 0; j < size(); ++j) {
            char c = board[i][j];
            int border_s_i = cell_size*i ;
            int border_s_j = cell_size*j ;

           if(c == 'X'){
               int idx  =0 ; // mirror reflection to Draw 'X'
               int i_start, j_start, i_end, j_end;
               i_start = border_s_i + 20;
               j_start = border_s_j + 20;

               i_end = border_s_i + cell_size - 20;
               j_end = border_s_j + cell_size - 20;
               for (int k = i_start , kj = j_start; k < i_end && j_end ; ++k ,++kj) {
                   image[k][kj] = {255,0,0};
                   image[k][j_end - idx] = {255,0,0};
                   ++idx;
               }
           }

             if (c == 'O'){
               // finding the center of the border
                int center_i = border_s_i + (cell_size/2);
                int center_j = (border_s_j) + (cell_size/2) ;
                double radius = (cell_size/2) -10;
                double radius_sqr = sqrt(radius);

// //                image[center_i][center_j] = {0,0,0};

                for (int ik = border_s_i + 10; ik < border_s_i + cell_size - 10; ++ik) {
                    for (int jl = border_s_j + 10; jl < border_s_j + cell_size- 10; ++jl) {
                        double calc_radius = pow((center_i - ik), 2) + pow((center_j - jl),2);
                        calc_radius = sqrt(calc_radius);
                        if(calc_radius == radius || (calc_radius < radius && calc_radius > radius -radius_sqr)){
                            image[ik][jl] = {255,0,0};
                        }
                    }
                }
            }


//            else continue; // '.' just dont do nothing
            
        }
        
    }
    ///
    ///image processing
    ///
    imageFile.write(reinterpret_cast<char*>(&image), 3*dimx*dimy);
    imageFile.close();
    return fileName;
}








