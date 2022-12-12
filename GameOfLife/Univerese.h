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
const char NINE_ASCCI = (char)(9 - '0');
const char SPACE_ASCCI = ' ';
class universe{
public:
    universe(string);
    string get_game_version(vector <string>);
    string get_universe_name(vector <string>);
    vector<vector<int>> get_coords(vector <string>);
    void set_gamerule(vector <string>);
    void set_height_and_width(vector <string>);



private:
    string game_version;
    string universe_name;

    int height;
    int width;

    vector<int> game_rule_to_alive_count;
    vector<int> game_rule_to_survive_count;
    vector<vector<int>> coords;
};

#endif
