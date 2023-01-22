#include "gtest/gtest.h"
#include "GameConsole.h"
#include "GameConsole.cpp"

#include "GameField.h"
#include "GameField.cpp"

#include "Univerese.h"
#include "Universe.cpp"

#include "GameInterface.h"
#include "GameInterface.cpp"


namespace game{
    TEST(GameTest, name_and_rules_from_file) {
        std::ifstream test_file;
        test_file.open("file_test.txt");

        gamefield game(test_file);


        std::vector<int> game_rule_to_alive_count_t{1, 2, 3, 4, 5};
        std::vector<int> game_rule_to_survive_count_t{2, 4, 8};

        ASSERT_EQ(game.get_universe_name(), "rules_name_test");
        ASSERT_EQ(game.get_survive_rule(), game_rule_to_survive_count_t);
        ASSERT_EQ(game.get_alive_rule(), game_rule_to_alive_count_t);
    }

    TEST(GameTest, alive_cells_from_file) {
        std::ifstream test_file;
        test_file.open("cells.txt");

        gamefield game(test_file);

        ASSERT_EQ(game.get_cell(0, 0), ALIVE);
        ASSERT_EQ(game.get_cell(1, 0), ALIVE);
        ASSERT_EQ(game.get_cell(0, 1), ALIVE);
        ASSERT_EQ(game.get_cell(1, 1), ALIVE);

    }

    TEST(GameTest, height_and_width_from_file) {
        std::ifstream test_file;
        test_file.open("height_width.txt");

        gamefield game(test_file);
        ASSERT_EQ(game.get_length(), 10);
        ASSERT_EQ(game.get_width(), 20);

    }

    TEST(GameTest, neightbours_count) {
        std::ifstream test_file;
        test_file.open("neightbours.txt");

        gamefield game(test_file);

        ASSERT_EQ(game.neighbors_count(0, 0), 4);
        ASSERT_EQ(game.neighbors_count(1, 0), 4);
        ASSERT_EQ(game.neighbors_count(1, 1), 3);
        ASSERT_EQ(game.neighbors_count(0, 1), 3);
        ASSERT_EQ(game.neighbors_count(0, 3), 2); //toroidal

    }

    TEST(GameTest, game_tick) {
        std::ifstream test_file;
        test_file.open("tick.txt");

        gamefield game(test_file);

        game.tick(1);

        ASSERT_EQ(game.get_cell(0, 2), ALIVE);
        ASSERT_EQ(game.get_cell(1, 2), ALIVE);
        ASSERT_EQ(game.get_cell(2, 2), ALIVE);

        game.tick(1);

        ASSERT_EQ(game.get_cell(1, 1), ALIVE);
        ASSERT_EQ(game.get_cell(1, 2), ALIVE);
        ASSERT_EQ(game.get_cell(1, 3), ALIVE);

    }

    TEST(GameTest, dump_file) {
        std::ifstream test_file;
        test_file.open("dump.txt");

        gamefield game(test_file);

        game.dump("dump_out.txt");

        std::ifstream test_file_out;
        test_file_out.open("dump_out.txt");

        gamefield tmp(test_file_out);


        ASSERT_EQ(game.get_cur_field(), tmp.get_cur_field());
    }

}
    int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
