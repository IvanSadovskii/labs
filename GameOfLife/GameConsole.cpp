#include "GameConsole.h"

void console::choose_mod() { //cюда запихать еще параметры входной строки но можно и просто вводом
    std::cout<<"Plese enter game mode: 1 - for online mod, 2 - for offline mod\n";
    int mode;

    online_interface online;
    offline_interface offline;

    do {
        std::cin>>mode;
        if (mode == 1) {
            launch_programm(online);
            break;
        }
        else if (mode == 2) {
            launch_programm(offline);
            break;
        }
        std::cout<<"Error entering gamemode, please write the right number\n";
    } while(mode != 1 && mode != 2);
}
void console::launch_programm(interface & mode) {
    std::string input_file_path;
    std::cout<<"Enter input file:";
    std::cin>>input_file_path;

    mode.startGame(input_file_path); //cюда  добавить ввод файла
}



