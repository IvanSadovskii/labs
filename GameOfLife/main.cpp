#include "GameField.h"
#include "Univerese.h"


int main() {
    /*gamefield f(5,10);
    f.set_life(2,0);
    f.set_life(2,1);
    f.set_life(2,2);
    f.set_life(1,2);
    f.set_life(0,1);


    do {
        f.print_field();
        std::cout<<"\n";
        f.make_iteration();
    } while(!f.is_field_empty());*/
    setlocale(LC_ALL, "ru");

    universe world("test.txt");

    cout<<world.game_version<<"\n";
    cout<<world.universe_name<<"\n";
    cout<<world.height<<"\n";
    cout<<world.width<<"\n";

    for(int i = 0; i<world.game_rule_to_alive_count.size(); i++){
        cout<<world.game_rule_to_alive_count[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<world.game_rule_to_survive_count.size(); i++){
        cout<<world.game_rule_to_survive_count[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<world.coords.size(); i++){
        for (int j = 0; j<world.coords[i].size(); j++)
            cout<<world.coords[i][j]<<" ";
    }



    return 0;
}
