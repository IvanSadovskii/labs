#include "GameField.h"



gamefield::gamefield(std::ifstream &file) {
    string str;

    while (!file.eof()) {
        getline(file, str);
        line_indificator(str);
    }

    this->input_check();


    cur_field = vector<vector<bool>>(length,vector<bool>(width));
    neighbors = vector<vector<int>>(length,vector<int>(width));


    for (int i = 0; i<coords.size(); i++){
        set_life(coords[i][X_COORD_ID],coords[i][Y_COORD_ID]);
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
            if (!cur_field[i][j])
            cout<<"#";
            else cout<<"*";
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
            if (cur_field[i][j] == ALIVE) {
                bool is_cell_survive = false;

                for (int id_survive = 0; id_survive < game_rule_to_survive_count.size(); id_survive++) {
                    if (neighbors[i][j] == game_rule_to_survive_count[id_survive]) is_cell_survive = true;
                }
                if (!is_cell_survive) cur_field[i][j] = DEAD;
            }
            else {
                for (int id_alive = 0; id_alive < game_rule_to_alive_count.size(); id_alive++) {
                    if (neighbors[i][j] == game_rule_to_alive_count[id_alive]) set_life(i, j);
                }
            }
        }
    }
}

bool gamefield::is_field_empty() {
    int count = 0;
    for (int i = 0; i<length; i++){
        for (int j = 0; j<width; j++){
            count+=neighbors[i][j];
        }
    }
    if (count == 0) return true;
    else return false;
}

void gamefield::game_until_last_generation() {
    do {
        (*this).print_field();
        std::cout<<"\n";
        (*this).make_iteration();
    } while(!(*this).is_field_empty());
}
