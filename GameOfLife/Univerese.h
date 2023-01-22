#ifndef LABS_UNIVERESE_H
#define LABS_UNIVERESE_H

#include <iostream>
#include "fstream"
#include "string"
#include "vector"

namespace game {
    const std::string CURRENT_GAME_VERSION = "#Life 1.06";
    const char BIRTH = 'B';
    const char SURVIVAL = 'S';
    const char SLASH_ASCII = '/';
    const char NINE_ASCCI = (char) (9 + '0');
    const char SPACE_ASCCI = ' ';
    const std::string GAME_VERSION_COMMENT = "#Li";
    const std::string UNIVERSE_NAME_COMMENT = "#N ";
    const std::string GAME_RULES_COMMENT = "#R ";
    const std::string DEFAULT_UNIVERSE_NAME = "DEFULT_UNIVERSE";
    const int DEFAULT_LENGTH = 10;
    const int DEFAULT_WIDTH = 20;
    const int X_COORD_ID = 0;
    const int Y_COORD_ID = 1;
    const int NUMBER_OF_COORDS = 2;

    const std::vector<int> default_game_rule_to_alive_count = {3};
    const std::vector<int> default_game_rule_to_survive_count = {2, 3};

    const int MIN_FIRST_INPUT_SYMBOLS_COUNT = 3;

    class universe {
    public:
        ~universe();

        void set_game_version(std::string);

        void set_universe_name(std::string);

        void set_coords(std::string);

        void set_gamerule(std::string);

        void set_length_and_width(std::string);

        void line_indificator(std::string, bool);

        void input_check();

        std::string get_universe_name();

        std::vector<int> get_alive_rule();

        std::vector<int> get_survive_rule();

        int get_length();

        int get_width();


    protected:
        std::string game_version;
        std::string universe_name;

        int length;
        int width;

        bool is_there_length_width_in_file = false;
        bool is_there_game_version_in_file = false;
        bool is_there_unversity_name_in_file = false;
        bool is_there_game_rules_in_file = false;
        bool is_there_coords_in_life = false;

        std::vector<int> game_rule_to_alive_count;
        std::vector<int> game_rule_to_survive_count;
        std::vector<std::vector<int>> coords;
    };
}
#endif
