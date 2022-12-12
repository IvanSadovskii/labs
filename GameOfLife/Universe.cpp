#include "Univerese.h"


universe::universe(std::string path) { //обработать все ошибки - потом
    ifstream file;
    file.open(path);

    if (!file.is_open()){
        throw std::invalid_argument("Ошибка при открытии файла\n");
    }
    else {
        vector<string> tmp_str;
        string str;

        while (!file.eof()) {
            getline(file, str);
            tmp_str.push_back(str);
        }

        game_version = get_game_version(tmp_str);
        universe_name = get_universe_name(tmp_str);
        (*this).set_gamerule(tmp_str);
        (*this).set_height_and_width(tmp_str);






    }




}
string universe::get_game_version(vector<string> str_tmp) {
    if (!str_tmp.empty() && str_tmp[0] == CURRENT_GAME_VERSION ) return str_tmp[0];
    else {
        throw std::invalid_argument("Ошибка ввода версии\n");
    }
}

string universe::get_universe_name(vector<string> str_tmp) { //забыл про #N
    if (str_tmp.size() > 1 && !str_tmp[1].empty()) return str_tmp[1];
    else {
        throw std::invalid_argument("Ошибка ввода имени вселенной\n");
    }

}

void universe::set_gamerule(vector<string> str_tmp) { //забыл про #R
    string buffer;

    if (str_tmp.size() > 2 && !str_tmp[2].empty()) buffer = str_tmp[2];
    else {
        throw std::invalid_argument("Ошибка ввода правил игры\n");
    }

    int index = 0;
    int rule_flag = 0;

    if (buffer[index] != BIRTH) throw std::invalid_argument("Ошибка ввода правил игры\n");
    index++;

    while (index < buffer.length()) {

        if (buffer[index] == SLASH_ASCII && rule_flag == 0) {
            rule_flag = 1;
            index++;
            if ((index == buffer.length() - 1) || buffer[index] != SURVIVAL) throw std::invalid_argument("Ошибка ввода правил игры \n");
            else index++;
        }

        if ((index == buffer.length() - 1) || !isdigit(buffer[index]) || buffer[index] == NINE_ASCCI){
            throw std::invalid_argument("Ошибка ввода правил игры\n");
        }

        if (rule_flag == 0) {
            game_rule_to_alive_count.push_back((int) (buffer[index] + '0')); //как то переделать
        }
        else {
            game_rule_to_survive_count.push_back((int) (buffer[index] + '0'));
        }
        index++;
    }
}

void universe::set_height_and_width(vector<string> str_tmp) {
    string buffer;
    string first_number;
    string second_number;
    int number_flag = 0;

    if (str_tmp.size() > 3 && !str_tmp[3].empty()) buffer = str_tmp[3];
    else {
        throw std::invalid_argument("Ошибка ввода размера поля\n");
    }
    for (int i = 0; i<buffer.length() - 1; i++){
        if (buffer[i] == SPACE_ASCCI && number_flag == 0) {
            if (i == 0) throw std::invalid_argument("Ошибка ввода размера поля\n");
            number_flag = 1;
            continue;
        }
        if (!isdigit(buffer[i])) throw std::invalid_argument("Ошибка ввода размера поля\n");

        if (number_flag == 0){
            first_number+=buffer[i];
        }
        else second_number+=buffer[i];
    }
    height = stoi(first_number);
    width = stoi(second_number);

}



vector<vector<int>> universe::get_coords(vector<string>){

}