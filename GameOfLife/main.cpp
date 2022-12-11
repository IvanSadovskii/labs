#include "GameField.h"

int main() {
    gamefield f(10,20);
    f.set_life(0,0);
    f.set_life(1,0); //
    f.set_life(2,0);

    f.print_field();
    std::cout<<"\n";
    f.make_iteration();
    f.print_field();

    std::cout<<"\n";
    f.make_iteration();
    f.print_field();

    //std::cout<<"\n"<< f.neighbors_count(1,1);
    return 0;
}
