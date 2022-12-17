#include "GameInterface.h"



void online_interface::startGame(std::string path) { //здесь еще итерации и выходной файл while true и т.д
    ifstream cur_file;
    cur_file.open(path);

    if (!cur_file.is_open()){
        std::cout<<"Error opening current file\n";
        cur_file.close();
        cur_file.open("defult.txt");
    }

    gamefield game(cur_file);
    game.game_until_last_generation();


}
void console::choose_mod() { //cюда запихать еще параметры входной строки но можно и просто вводом
    std::cout<<"Plese enter game mode: 1 - for online mod, 2 - for offline mod\n";
    int mode;
    std::cin>>mode;

    online_interface online;

    if (mode == 1) launch_programm(online);
}
void console::launch_programm(interface & mode) {
    mode.startGame("test.txt"); //cюда  добавить ввод файла
}
