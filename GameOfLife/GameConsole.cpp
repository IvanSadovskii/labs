#include "GameConsole.h"
namespace game {
    void console::choose_mod() {
        std::cout << "Plese enter game mode: 1 - for online mod, 0 - for offline mod\n";
        int mode;

        online_interface online;
        offline_interface offline;

        do {
            std::cin >> mode;
            if (mode == ONLINE) {
                launch_programm(online);
                break;
            } else if (mode == OFFLINE) {
                launch_programm(offline);
                break;
            }
            std::cout << "Error entering gamemode, please write the right number\n";
        } while (mode != ONLINE && mode != OFFLINE);
    }

    void console::launch_programm(interface &mode) {
        std::string input_file_path;
        std::cout << "Enter input file:";
        std::cin >> input_file_path;

        mode.startGame(input_file_path);
    }
}


