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

    std::cout<<"Enter the command (help - for information about commands)\n";

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
        if (command == "dump"){
            std::string out_path;
            std::cin>>out_path;
            game.dump(out_path);
        }

        if (command == "exit") {
            cur_file.close();
            return;
        }
    }

}

void online_interface::print_help(){
    std::cout<<"dump <file name> - save the universe to a file\n";
    std::cout<<"tick <n=1> (and t <n=1> for short) - calculate n (default 1) iterations and print the result\n";
    std::cout<<"exit - end the game\n";
    std::cout<<"help - print help about commands\n";
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

void offline_interface::startGame(std::string path) {
    ifstream cur_file;
    std::string command;
    std::string output_path;
    int iterations;

    cur_file.open(path);

    if (!cur_file.is_open()){
        std::cout<<"Error opening current file\n";
        cur_file.close();
        cur_file.open("defult.txt");
    }

    gamefield game(cur_file);

    std::cout<<"Enter number of iterations:";
    std::cin>>iterations;

    std::cout<<"Enter output file:";
    std::cin>>output_path;

    game.tick(iterations);
    game.dump(output_path);

    cur_file.close();
}

