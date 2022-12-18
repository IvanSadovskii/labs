#include "GameInterface.h"



void online_interface::startGame(std::string path) { //здесь еще итерации и выходной файл while true и т.д
    ifstream cur_file;
    std::string command;
    int iteration_count = 0;

    cur_file.open(path);

    if (!cur_file.is_open()){
        std::cout<<"Error opening current file\n";
        cur_file.close();
        cur_file.open("defult.txt");
    }

    gamefield game(cur_file);
    while (true){
        std::cin>>command;
        if (command == "help") (*this).print_help();

        if (command == "tick") {
            int n = 1;
            std::cin>>n; //тут вроде не обязательно вводить??
            game.tick(n);

            iteration_count+=n;
            (*this).print_game_field_informaton(game,iteration_count);
        }

        if (command == "exit") return;
    }


}

void online_interface::print_help(){
    std::cout<<"dump <filename> - сохранить вселенную в файл\n";
    std::cout<<"tick <n=1> (и сокращенно t <n=1>) - рассчитать n (по умолчанию 1) итераций и напечатать результат\n";
    std::cout<<"exit – завершить игру\n";
    std::cout<<"help – распечатать справку о командах\n";
}

void online_interface::print_game_field_informaton(gamefield &field, int iteration_number) {
    vector<int> tmp;
    std::cout<<field.get_universe_name()<<"\n";

    std::cout<<"B";
    tmp = field.get_alive_rule();
    for (int i = 0; i<tmp.size(); i++) std::cout<<tmp[i];
    std::cout<<"/S";
    tmp = field.get_survive_rule();
    for (int i = 0; i<tmp.size(); i++) std::cout<<tmp[i];
    std::cout<<"\n";

    std::cout<<"Number of iteration:"<<iteration_number<<"\n";

    field.print_field();
    tmp.clear();
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
