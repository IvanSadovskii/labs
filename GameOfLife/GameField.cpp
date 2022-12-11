#include "GameField.h"

gamefield::gamefield(int length, int width) {
    this->width = width;
    this->length = length;

    neighbors.reserve(length);
    cur_field.reserve(length); //на два в ширину и на два в длину


    for (int i = 0; i<length; i++){
        neighbors[i].resize(width);
        cur_field[i].resize(width);
        for(int j = 0; j<width; j++){
            cur_field[i][j] = DEAD;
            neighbors[i][j] = 0;
        }
    }



}
gamefield::~gamefield() {
    cur_field.clear();
    neighbors.clear();
}

int gamefield::coord_mod(int x, int y) { //y - это длина или ширина
    int result;
    int x_c = x+1;

    result = x_c % y;

    if (result == 0) return y - 1;
    else return result - 1;
}


void gamefield::print_field() {
    for (int i = 0; i<length; i++){
        for (int j = 0; j<width; j++){
            std::cout<<cur_field[i][j];
        }
        std::cout<<"\n";
    }
}

void gamefield::set_life(int x, int y) {
    cur_field[x][y] = ALIVE;

}
int gamefield::neighbors_count(int x, int y) {
    return (cur_field[coord_mod(x+1+length,length)][coord_mod(y+width,width)]+
            cur_field[coord_mod(x-1+length,length)][coord_mod(y+width,width)]+
            cur_field[coord_mod(x+1+length,length)][coord_mod(y+1+width,width)]+
            cur_field[coord_mod(x-1+length,length)][coord_mod(y+1+width,width)]+
            cur_field[coord_mod(x+1+length,length)][coord_mod(y-1+width,width)]+
            cur_field[coord_mod(x-1+length,length)][coord_mod(y-1+width,width)]+
            cur_field[coord_mod(x+length,length)][coord_mod(y+1+width,width)]+
            cur_field[coord_mod(x+length,length)][coord_mod(y-1+width,width)]
    );
}

void gamefield::make_iteration() {
    for (int i = 0; i<length; i++){
        for (int j = 0; j<width; j++){
            neighbors[i][j] = this->neighbors_count(i,j);
        }
    }

    for (int i = 0; i<length; i++){
        for (int j = 0; j<width; j++){
            if (neighbors[i][j] == 3) set_life(i,j);
            else if (neighbors[i][j] > 3 || neighbors[i][j] < 2) cur_field[i][j] = DEAD;
        }
    }
}
