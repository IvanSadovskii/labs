#ifndef LABS_UNIVERESE_H
#define LABS_UNIVERESE_H

#include <iostream>
#include "fstream"
#include "string"
#include "vector"

using namespace std;
const string CURRENT_GAME_VERSION = "#Life 1.06";
const char BIRTH = 'B';
const char SURVIVAL = 'S';
const char SLASH_ASCII= '/';
const char NINE_ASCCI = (char)(9 + '0');
const char SPACE_ASCCI = ' ';
const string GAME_VERSION_COMMENT = "#Li";
const string UNIVERSE_NAME_COMMENT = "#N ";
const string GAME_RULES_COMMENT = "#R ";
const int X_COORD_ID = 0;
const int Y_COORD_ID = 1;

const int MIN_FIRST_INPUT_SYMBOLS_COUNT = 3;

class universe{
public:
    ~universe();
    void get_game_version(string);
    void get_universe_name(string);
    void get_coords(string);
    void set_gamerule(string);
    void set_length_and_width(string);
    void line_indificator(string);
    void input_check();



protected: //поменять на private после тестов
    string game_version;
    string universe_name;

    int length;
    int width;

    bool is_there_length_width_in_file = false;
    bool is_there_game_version_in_file = false;
    bool is_there_unversity_name_in_file = false;
    bool is_there_game_rules_in_file = false;
    bool is_there_coords_in_life = false;

    vector<int> game_rule_to_alive_count;
    vector<int> game_rule_to_survive_count;
    vector<vector<int>> coords;
};

#endif
