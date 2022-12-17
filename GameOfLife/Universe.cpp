#include "Univerese.h"

universe::~universe() {
    this->coords.clear();
    this->game_rule_to_survive_count.clear();
    this->game_rule_to_alive_count.clear();
}

void universe::get_game_version(string str_tmp) {
    if (!str_tmp.empty() && str_tmp == CURRENT_GAME_VERSION ) {
        is_there_game_version_in_file = true;
        game_version = str_tmp;
    }
}

void universe::get_universe_name(string str_tmp) { //забыл про #N
    if (!str_tmp.empty()) {
        is_there_unversity_name_in_file = true;
        universe_name = str_tmp;
    }

}

void universe::set_gamerule(string buffer) {//забыл про #R

    int index = 0;
    int rule_flag = 0;

    if (buffer[index] != BIRTH) throw std::invalid_argument("Error entering game rules1\n");
    index++;

    while (index < buffer.length()) {

        if (buffer[index] == SLASH_ASCII && rule_flag == 0) {
            rule_flag = 1;
            index++;
            if ((index == buffer.length() - 1) || buffer[index] != SURVIVAL) throw std::invalid_argument("Error entering game rules2\n");
            else {
                index++;
            }
        }

        if (!isdigit(buffer[index]) || buffer[index] == NINE_ASCCI){
            throw std::invalid_argument("Error entering game rules3\n");
        }

        if (rule_flag == 0) {
            game_rule_to_alive_count.push_back((int) (buffer[index] - '0')); //как то переделать
        }
        else {
            game_rule_to_survive_count.push_back((int) (buffer[index] - '0'));
        }
        index++;
    }
    is_there_game_rules_in_file = true;
}

void universe::set_length_and_width(string buffer) {
    string first_number;
    string second_number;
    int number_flag = 0;

    for (int i = 0; i<buffer.length(); i++){
        if (buffer[i] == SPACE_ASCCI && number_flag == 0) {
            if (i == 0) throw std::invalid_argument("Error entering field size1\n");
            number_flag = 1;
            continue;
        }
        if (!isdigit(buffer[i])) throw std::invalid_argument("Error entering field size2\n");

        if (number_flag == 0){
            first_number+=buffer[i];
        }
        else second_number+=buffer[i];
    }
    length = stoi(first_number);
    width = stoi(second_number);
    is_there_length_width_in_file = true;
}

void universe::get_coords(string buffer) {
    string first_number;
    string second_number;
    int number_flag = 0;

    for (int i = 0; i<buffer.length(); i++){
        if (buffer[i] == SPACE_ASCCI && number_flag == 0) {
            if (i == 0) throw std::invalid_argument("Error entering coordinates1\n");
            number_flag = 1;
            continue;
        }
        if (!isdigit(buffer[i])) throw std::invalid_argument("Error entering coordinates2\n");

        if (number_flag == 0){
            first_number+=buffer[i];
        }
        else second_number+=buffer[i];
    }

    coords.resize(coords.size()+1);
    coords[coords.size() - 1].resize(2); //убрать магию
    coords[coords.size() - 1][0] = stoi(first_number); //x
    coords[coords.size() - 1][1] = stoi(second_number); //y
    is_there_coords_in_life = true;

}



void universe::line_indificator(string str) {
    if (str.empty() || str.size() < MIN_FIRST_INPUT_SYMBOLS_COUNT) throw std::invalid_argument("Error entering file format\n");

    string str_comment = str.substr(0,MIN_FIRST_INPUT_SYMBOLS_COUNT);

    if (str_comment == GAME_VERSION_COMMENT) {
        (*this).get_game_version(str);
        return;
    }
    if (str_comment == UNIVERSE_NAME_COMMENT){
        (*this).get_universe_name(str.substr(MIN_FIRST_INPUT_SYMBOLS_COUNT));
        return;
    }
    if (str_comment == GAME_RULES_COMMENT) {
        (*this).set_gamerule(str.substr(MIN_FIRST_INPUT_SYMBOLS_COUNT));
        return;
    }
    if (!is_there_length_width_in_file){
        (*this).set_length_and_width(str);
    }
    else {
        (*this).get_coords(str);
    }
}

void universe::input_check() {
    if (!is_there_game_version_in_file){
        throw std::invalid_argument("File missing game version 1.06\n"); //здесь добавить дефолтные значения
    }
    if (!is_there_unversity_name_in_file){
        cout<<"The file is missing a universe name\n";
    }
    if (!is_there_game_rules_in_file){
        cout<<"File is missing game rules\n";
    }
    if (!is_there_length_width_in_file){
        cout<<"The file is missing a universe length and width\n";
    }
    if (!is_there_coords_in_life){
        throw std::invalid_argument("The file does not contain the coordinates of live cells\n");
    }
}