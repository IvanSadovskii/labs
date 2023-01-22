#include "GameField.h"

namespace game {

    gamefield::gamefield(std::ifstream &file) {
        std::string str;

        while (!file.eof()) {
            getline(file, str);
            line_indificator(str, file.eof());
        }

        this->input_check();


        cur_field = std::vector<std::vector<bool>>(length, std::vector<bool>(width));
        neighbors = std::vector<std::vector<int>>(length, std::vector<int>(width));


        for (int i = 0; i < coords.size(); i++) {
            set_life(coords[i][X_COORD_ID], coords[i][Y_COORD_ID]);
        }
    }

    gamefield::~gamefield() {
        cur_field.clear();
        neighbors.clear();
    }

    int gamefield::coord_mod(int x, int y) {
        int result;
        int x_c = x + 1;

        result = x_c % y;

        if (result == 0) return y - 1;
        else return result - 1;
    }


    void gamefield::print_field() {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (!cur_field[i][j])
                    std::cout << "#";
                else std::cout << "O";
            }
            std::cout << "\n";
        }
    }

    void gamefield::set_life(int x, int y) {
        cur_field[x][y] = ALIVE;

    }

    int gamefield::neighbors_count(int x, int y) {
        return (cur_field[coord_mod(x + 1 + length, length)][coord_mod(y + width, width)] +
                cur_field[coord_mod(x - 1 + length, length)][coord_mod(y + width, width)] +
                cur_field[coord_mod(x + 1 + length, length)][coord_mod(y + 1 + width, width)] +
                cur_field[coord_mod(x - 1 + length, length)][coord_mod(y + 1 + width, width)] +
                cur_field[coord_mod(x + 1 + length, length)][coord_mod(y - 1 + width, width)] +
                cur_field[coord_mod(x - 1 + length, length)][coord_mod(y - 1 + width, width)] +
                cur_field[coord_mod(x + length, length)][coord_mod(y + 1 + width, width)] +
                cur_field[coord_mod(x + length, length)][coord_mod(y - 1 + width, width)]
        );
    }

    void gamefield::make_iteration() {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                neighbors[i][j] = this->neighbors_count(i, j);
            }
        }

        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (cur_field[i][j] == ALIVE) {
                    bool is_cell_survive = false;

                    for (int id_survive = 0; id_survive < game_rule_to_survive_count.size(); id_survive++) {
                        if (neighbors[i][j] == game_rule_to_survive_count[id_survive]) is_cell_survive = true;
                    }
                    if (!is_cell_survive) cur_field[i][j] = DEAD;
                } else {
                    for (int id_alive = 0; id_alive < game_rule_to_alive_count.size(); id_alive++) {
                        if (neighbors[i][j] == game_rule_to_alive_count[id_alive]) set_life(i, j);
                    }
                }
            }
        }
    }

/*ool gamefield::is_field_empty() {
    int count = 0;
    for (int i = 0; i<length; i++){
        for (int j = 0; j<width; j++){
            count+=neighbors[i][j];
        }
    }
    if (count == 0) return true;
    else return false;
}*/

    void gamefield::tick(int n) {
        for (int i = 0; i < n; i++) {
            (*this).make_iteration();
        }
    }

    void gamefield::dump(std::string path) {
        std::ofstream file;
        file.open(path);

        if (!file.is_open()) {
            std::cout << "Out file warn\n";
            file.close();
            return;
        }

        file << (*this).game_version << "\n";
        file << "#N " << (*this).universe_name << "\n";
        file << "#R B";
        for (int i = 0; i < game_rule_to_alive_count.size(); i++) file << game_rule_to_alive_count[i];
        file << "/S";
        for (int i = 0; i < game_rule_to_survive_count.size(); i++) file << game_rule_to_survive_count[i];
        file << "\n";
        file << length << " " << width << "\n";

        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (cur_field[i][j] == ALIVE) file << i << " " << j << "\n";
            }
        }

        file.close();
    }

    bool gamefield::get_cell(int x_cord, int y_cord) {
        return (*this).cur_field[x_cord][y_cord];
    }

    std::vector<std::vector<bool>> gamefield::get_cur_field() {
        return (*this).cur_field;
    }
}